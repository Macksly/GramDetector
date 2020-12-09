#include "AutoGramController.h"
#include <iostream>
#include <chrono>
using namespace std::this_thread;
using namespace std::chrono_literals;

GramDetector::Controllers::AutoGramController::AutoGramController(const std::shared_ptr<GramDetector::Models::RandomEngine>& random)
    : _random{ random }, _iterations{ 0 }, _letters{ 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' }, _dist{1,200} {}

void GramDetector::Controllers::AutoGramController::start(const std::string& input, const GramDetector::Enums::LanguageEnum& lang)
{
    int seedCounter = 1;
    bool succes = false;

    _iterationsThread = std::thread(&GramDetector::Controllers::AutoGramController::printElapsedIterations, this);
    
    std::string seed;
    while (!succes) {
        seed = input;

        for (int i{ 0 }; i < 5; ++i) {
            seed.append(" " + _dbCtrl.getValue(lang, _dist(_random->getInstance())));
        }

        std::cout << "New Seed Created (Nr: " << seedCounter << ") " << seed << std::endl;

        if (findAutogram(seed, lang, input)) {
            _iterationsThread.detach();
            succes = true;
        }
        else {
            ++seedCounter;
        }
    }
}

void GramDetector::Controllers::AutoGramController::printElapsedIterations() {
    while (true) {
        sleep_for(1000ms);
        std::cout << "Iterations per second: " << std::to_string(_iterations) << std::endl;
        _iterations = 0;
    }
}

const bool GramDetector::Controllers::AutoGramController::findAutogram(std::string& seed, const Enums::LanguageEnum& lang, const std::string& input)
{
    int iterationCounter = 0;

    while (iterationCounter <= 20) {
        std::vector<std::pair<char, std::size_t>> oldAmounts = countSentence(seed);

        std::string result = createSentence(input, lang, oldAmounts);

        std::vector<std::pair<char, std::size_t>> newAmounts = countSentence(result);

        if (oldAmounts == newAmounts) {
            std::cout << "Autogram found at iteration " << iterationCounter << ": " << result << std::endl;
            return true;
        }
        else {
            seed = result;
            ++iterationCounter;
        }
    }

    return false;
}

const std::string GramDetector::Controllers::AutoGramController::createSentence(const std::string& input, const Enums::LanguageEnum& lang, const std::vector<std::pair<char, std::size_t>>& amounts)
{
    std::string retVal = input;

    for (std::pair<char, std::size_t> pair : amounts) {
        retVal.append(" " + _dbCtrl.getValue(lang, pair.second) + " " + pair.first + "'s,");
    }

    return retVal;
}

const std::vector<std::pair<char, std::size_t>> GramDetector::Controllers::AutoGramController::countSentence(const std::string& seed)
{
    std::vector<std::pair<char, std::size_t>> temp = {};

    for (char p : _letters) {
        std::size_t amount = std::count(seed.begin(), seed.end(), p);

        if (amount > 0) {
            temp.push_back(std::pair<char, std::size_t>(p, amount));
        }
        ////else {
        ////    temp.push_back(std::pair<char, std::size_t>(p, 1));
        ////}
    }

    ++_iterations;
    return temp;
}