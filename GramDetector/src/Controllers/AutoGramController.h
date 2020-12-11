#pragma once
#include "DatabaseController.h"
#include "../Models/RandomEngine.h"
#include <string>
#include <memory>
#include <thread>

namespace GramDetector {
	namespace Controllers {
		class IOController;

		class AutoGramController {
		public:
			AutoGramController(const std::shared_ptr<Models::RandomEngine>& random, const std::shared_ptr<Controllers::IOController>& input);
			void start(const std::string& input, const Enums::LanguageEnum& lang, bool pangrammode);

		private:
			const std::vector<char> _letters;
			const std::uniform_int_distribution<int> _dist;
			const std::shared_ptr<Models::RandomEngine> _random;
			const std::shared_ptr<Controllers::IOController> _ioCtrl;

			DatabaseController _dbCtrl;
			std::thread _iterationsThread;
			int _iterations;
			int _seconds;
			bool _success;

			bool findAutogram(std::string& seed, const Enums::LanguageEnum& lang, const std::string& input, bool pangrammode);

			std::string createSentence(const std::string& seed, const Enums::LanguageEnum& lang, const std::vector<std::pair<char, std::size_t>>& amounts);
			std::string createSeed(const std::string& input, const Enums::LanguageEnum& lang);
			std::vector<std::pair<char, std::size_t>> countSentence(const std::string& value, bool pangrammode);

			void printElapsedIterations();
		};
	}
}

