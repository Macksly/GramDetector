#pragma once
#include "../Models/RandomEngine.h"

namespace GramDetector {
	namespace Controllers {
		class IOController {
		public:
			std::string getSentence() const;
			const int getGramType() const;
			const int getLangType() const;
			void printSucces(const std::string& result, const int seconds, const std::string& input);
		};
	}
}