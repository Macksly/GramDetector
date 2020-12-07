#pragma once
#include "../Models/RandomEngine.h"
#include "InputController.h"
#include "DatabaseController.h"
#include "../Enums/TypeEnum.h"
#include <memory>
#include "AutoGramController.h"

namespace GramDetector {
	namespace Controllers {
		class MainController {
		private:
			std::shared_ptr<Models::RandomEngine> _randomEngine;
			std::unique_ptr<AutoGramController> _autogramCtrl;
			InputController _input;

			Enums::TypeEnum getGramType();
			Enums::LanguageEnum getLanguage();
		public:
			MainController();

			void run();
		};
	}
}