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
		public:
			DatabaseController();

			std::string getValue(const Enums::LanguageEnum& lang, int number);
			void loadAllValues(const Enums::LanguageEnum& lang);
		private:
			std::string findNumber(int left, int right, int number);
			std::vector<std::pair<int, std::string>> _curValues;
		};
	}
}