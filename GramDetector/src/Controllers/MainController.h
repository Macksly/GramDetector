#pragma once
#include "../Models/RandomEngine.h"
#include "IOController.h"
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
			const std::shared_ptr<Controllers::IOController> _ioCtrl;
			AutoGramController _autogramCtrl;

			const Enums::TypeEnum getGramType() const;
			const Enums::LanguageEnum getLanguage() const;
		};
	}
}