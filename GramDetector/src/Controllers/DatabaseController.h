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
			const std::string getValue(const Enums::LanguageEnum& lang, const int& number);
		};
	}
}