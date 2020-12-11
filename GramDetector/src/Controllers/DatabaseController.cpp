#include "DatabaseController.h"
#include <iostream>
#include "../Enums/LanguageEnum.h"
#include <filesystem>
#include <algorithm>
#include "../Helpers/BasePathHelper.h"

using namespace GramDetector;

Controllers::DatabaseController::DatabaseController() : _curValues{} {}

std::string Controllers::DatabaseController::getValue(const Enums::LanguageEnum& lang, int number)
{
    if (number > _curValues.at(_curValues.size() - 1).first ||
        number < _curValues.at(0).first) {
        throw std::exception("Number does not exist in database");
    }

    int pivot = (_curValues.size() - 1) / 2;

    if (_curValues.at(pivot).first == number) {
        return _curValues.at(pivot).second;
    }
    else if (_curValues.at(pivot).first < number) {
        return findNumber(pivot + 1, _curValues.size() - 1, number);
    }
    else {
        return findNumber(0, pivot - 1, number);
    }
}

std::string Controllers::DatabaseController::findNumber(int left, int right, const int number)
{
    int pivot = ((left + right) / 2);

    if (_curValues.at(pivot).first == number) {
        return _curValues.at(pivot).second;
    }
    else if (_curValues.at(pivot).first < number) {
        return findNumber(pivot + 1, right, number);
    }
    else {
        return findNumber(left, pivot - 1, number);
    }
}

void Controllers::DatabaseController::loadAllValues(const Enums::LanguageEnum& lang)
{
    sqlite3* db = {};
    int rc = sqlite3_open(std::string(Helpers::get_base_path() + "/assets/numerals.db").c_str(), &db);
    std::unique_ptr<sqlite3, int(*)(sqlite3*)> dbh{ db, sqlite3_close };

    if (rc) {
        throw std::exception("Cannot open database");
    }

    // create query
    std::string query = "SELECT value, num from numerals WHERE language_id == ";
    switch (lang) {
    case Enums::LanguageEnum::EN:
        query.append("2");
        break;
    default:
        query.append("1");
        break;
    }

    // create prepared statement
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    std::unique_ptr<sqlite3_stmt, int(*)(sqlite3_stmt*)> stmth{ stmt, sqlite3_finalize };

    if (rc != SQLITE_OK) {
        throw std::exception("Cannot create prepared stmt");
    }

    // execute prepared statement
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int num_val = (sqlite3_column_int(stmt, 0));
        std::string text_val = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        _curValues.push_back(std::make_pair(num_val, text_val));
    }

    if (rc != SQLITE_DONE) {
        throw std::exception("Something went wrong during the executing of the stmt");
    }

    std::sort(_curValues.begin(), _curValues.end());
}