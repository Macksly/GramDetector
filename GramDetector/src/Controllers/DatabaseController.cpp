#include "DatabaseController.h"
#include <iostream>
#include "../Enums/LanguageEnum.h"

using namespace GramDetector;

Controllers::DatabaseController::DatabaseController() {
    _records = {};
}

std::vector<std::pair<int, std::string>> Controllers::DatabaseController::getAllValues(Enums::LanguageEnum lang)
{
    std::vector<std::pair<int, std::string>> _retVal = {};
    sqlite3* db = {};

    if (openDb(db) != NULL) {
        return _retVal;
    }

    std::string query = "SELECT value, num from numerals WHERE language_id == ";
    switch (lang) {
    case GramDetector::Enums::LanguageEnum::EN:
        query.append("2");
    default:
        query.append("1");
    }


    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    char* zErrMsg = 0;

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return _retVal;
    }
    
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int number_normal = sqlite3_column_int(stmt, 0);
            std::string number_string = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

            // let's assume number can be NULL:
            _retVal.push_back(std::pair<int, std::string>(number_normal, number_string));
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }

    closeDb(db);

    return _retVal;
}

std::string Controllers::DatabaseController::getValue(Enums::LanguageEnum lang, int number)
{
    std::string _retVal;
    sqlite3* db = {};

    // open database
    int rc = sqlite3_open("D:/School - Programming/c++/Eindopdracht1/GramDetector/GramDetector/bin/Win32/Debug/assets/numerals.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
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
    char* zErrMsg = 0;

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return _retVal;
    }

    // execute prepared statement
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        _retVal = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }

    // destroy objects
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return _retVal;
}

int GramDetector::Controllers::DatabaseController::openDb(sqlite3* db)
{


    return 0;
}

void GramDetector::Controllers::DatabaseController::closeDb(sqlite3* db)
{

}