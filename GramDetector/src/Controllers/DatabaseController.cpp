#include "DatabaseController.h"
#include <iostream>
#include "../Enums/LanguageEnum.h"

using namespace GramDetector;

Controllers::DatabaseController::DatabaseController() {
    int rc = sqlite3_open("D:/School - Programming/c++/Eindopdracht1/GramDetector/GramDetector/bin/Win32/Debug/assets/numerals.db", &_db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(_db));
    }
}

//// copy constructor
//GramDetector::Controllers::DatabaseController::DatabaseController(const DatabaseController& other) : _db{ other._db }, _stmt{ other._stmt} {}
//
//// move constructor
//GramDetector::Controllers::DatabaseController::DatabaseController(DatabaseController&& other) : _db{ other._db }, _stmt{ other._stmt }
//{
//    this->~DatabaseController();
//}
//
//// copy operators
//GramDetector::Controllers::DatabaseController& GramDetector::Controllers::DatabaseController::operator=(const DatabaseController& other)
//{
//    if (this != &other) {
//        this->~DatabaseController();
//
//        _db = other._db;
//        _stmt = other._stmt;
//    }
//
//    return *this;
//}
//
//// move constructor
//GramDetector::Controllers::DatabaseController& GramDetector::Controllers::DatabaseController::operator=(DatabaseController&& other)
//{
//    if (this != &other) {
//        this->~DatabaseController();
//
//        _db = other._db;
//        _stmt = other._stmt;
//
//        other.~DatabaseController();
//    }
//
//    return *this;
//}


std::string Controllers::DatabaseController::getValue(Enums::LanguageEnum lang, int number)
{
    std::string _retVal;

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
    int rc = sqlite3_prepare_v2(_db, query.c_str(), -1, &_stmt, NULL);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error" << std::endl;
        return _retVal;
    }

    // execute prepared statement
    while ((rc = sqlite3_step(_stmt)) == SQLITE_ROW) {
        _retVal = reinterpret_cast<const char*>(sqlite3_column_text(_stmt, 0));
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "SELECT failed: " << sqlite3_errmsg(_db) << std::endl;
    }

    return _retVal;
}

GramDetector::Controllers::DatabaseController::~DatabaseController()
{
    sqlite3_finalize(_stmt);
    sqlite3_close(_db);
}
