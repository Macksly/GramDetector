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
		public:
			MainController();

			void run();
		private:
			const std::shared_ptr<Models::RandomEngine> _randomEngine;
			AutoGramController _autogramCtrl;
			InputController _input;

			const Enums::TypeEnum getGramType() const;
			const Enums::LanguageEnum getLanguage() const;
		};
	}
}