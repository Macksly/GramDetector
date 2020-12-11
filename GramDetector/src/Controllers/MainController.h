#pragma once
#include "../Models/RandomEngine.h"
#include "AutoGramController.h"
#include <memory>



namespace GramDetector {
	namespace Enums {
		enum class TypeEnum;
	}

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