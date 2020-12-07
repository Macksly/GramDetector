#pragma once
#include "../Models/RandomEngine.h"

namespace GramDetector {
	namespace Controllers {
		class InputController {
		public:
			std::string getSentence();
			int getGramType();
			int getLangType();
		};
	}
}