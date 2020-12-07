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
			std::vector<std::pair<std::string, int>> _records;

			int openDb(sqlite3* db);
			void closeDb(sqlite3* db);
		public:
			DatabaseController();

			std::vector<std::pair<int, std::string>> getAllValues(GramDetector::Enums::LanguageEnum lang);
			std::string getValue(Enums::LanguageEnum lang, int number);
		};
	}
}