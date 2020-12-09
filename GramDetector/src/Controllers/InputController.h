#pragma once
#include "../Models/RandomEngine.h"

namespace GramDetector {
	namespace Controllers {
		class InputController {
		public:
			const std::string getSentence() const;
			const int getGramType() const;
			const int getLangType() const;
		};
	}
}