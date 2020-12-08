#pragma once
#include <sqlite3.h>
#include <string>
#include <vector>

namespace GramDetector {
	namespace Enums {
		enum class LanguageEnum;
	}

	namespace Controllers {
		class DatabaseController {
		private:
			sqlite3* _db;
			sqlite3_stmt* _stmt;

		public:
			DatabaseController();

			DatabaseController(const DatabaseController& other) = delete;
			DatabaseController(DatabaseController&& other) = delete;
			DatabaseController& operator=(const DatabaseController& other) = delete;
			DatabaseController& operator=(DatabaseController&& other) = delete;

			std::string getValue(Enums::LanguageEnum lang, int number);

			~DatabaseController();
		};
	}
}