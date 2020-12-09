#pragma once
#include <string>
#include <memory>
#include "../Models/RandomEngine.h"
#include "DatabaseController.h"
#include <thread>

namespace GramDetector {
	namespace Controllers {
		class AutoGramController {
		public:
			AutoGramController(const std::shared_ptr<GramDetector::Models::RandomEngine>& random);
			void start(const std::string& input, const GramDetector::Enums::LanguageEnum& lang);

		private:
			const std::vector<char> _letters;
			const std::uniform_int_distribution<int> _dist;
			const std::shared_ptr<GramDetector::Models::RandomEngine> _random;

			DatabaseController _dbCtrl;
			std::thread _iterationsThread;
			int _iterations;

			const bool findAutogram(std::string& seed, const Enums::LanguageEnum& lang, const std::string& input);
			const std::string createSentence(const std::string& seed, const Enums::LanguageEnum& lang, const std::vector<std::pair<char, std::size_t>>& amounts);
			const std::vector<std::pair<char, std::size_t>> countSentence(const std::string& value);
			void printElapsedIterations();
		};
	}
}

