#pragma once
#include <string>
#include <memory>
#include "../Models/RandomEngine.h"
#include "DatabaseController.h"
#include <thread>

namespace GramDetector {
	namespace Controllers {
		class AutoGramController {
		private:
			std::shared_ptr<GramDetector::Models::RandomEngine> _random;
			DatabaseController _dbCtrl;
			std::vector<char> _letters;
			std::string _input;
			std::thread _iterationsThread;
			GramDetector::Enums::LanguageEnum _lang;
			int _iterations;
			bool _succes;

			bool findAutogram(std::string& seed);
			std::string createSentence(const std::string& seed, const std::vector<std::pair<char, std::size_t>>& amounts);
			std::vector<std::pair<char, std::size_t>> countSentence(const std::string&);
			void printElapsedIterations();

		public:
			AutoGramController(std::shared_ptr<GramDetector::Models::RandomEngine> random);
			bool start(std::string input, GramDetector::Enums::LanguageEnum lang);
		};
	}
}

