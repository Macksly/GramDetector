#include "DatabaseController.h"
#include <iostream>
#include "../Enums/LanguageEnum.h"
#include <filesystem>
#include "../Helpers/BasePathHelper.h"

using namespace GramDetector;

const std::string Controllers::DatabaseController::getValue(const Enums::LanguageEnum& lang, const int& number)
{
    std::string _retVal;
    sqlite3* db = {};
    int rc = sqlite3_open(std::string(Helpers::get_base_path() + "/assets/numerals.db").c_str(), &db);
    std::unique_ptr<sqlite3, int(*)(sqlite3*)> dbh{ db, sqlite3_close };

    if (rc) {
        std::cout << "Something went wrong during the creation of the database" << std::endl;
        return _retVal;
    }

    // create query
    std::string query = "SELECT num from numerals WHERE language_id == ";
    switch (lang) {
    case GramDetector::Enums::LanguageEnum::EN:
        query.append("2");
        break;
    default:
        query.append("1");
        break;
    }

    query.append(" AND value == ");
    query.append(std::to_string(number));

    // create prepared statement
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    std::unique_ptr<sqlite3_stmt, int(*)(sqlite3_stmt*)> stmth{ stmt, sqlite3_finalize };

    if (rc != SQLITE_OK) {
        std::cout << "Something went wrong during the creation of the prepared stmt" << std::endl;
        return _retVal;
    }

    // execute prepared statement
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        _retVal = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }

    return _retVal;
}