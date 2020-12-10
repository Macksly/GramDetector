#include "AutoGramController.h"
#include <iostream>
#include <chrono>
using namespace std::this_thread;
using namespace std::chrono_literals;
using namespace GramDetector;

Controllers::AutoGramController::AutoGramController(const std::shared_ptr<Models::RandomEngine>& random, const std::shared_ptr<Controllers::IOController>& ioCtrl)
    : _random{ random }, _iterations{ 0 }, _letters{ 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' }, _dist{ 1,200 }, _ioCtrl{ ioCtrl }, _success{ false }, _seconds{ 0 } {}

void Controllers::AutoGramController::start(const std::string& input, const Enums::LanguageEnum& lang, bool pangrammode )
{
    _iterationsThread = std::thread(&Controllers::AutoGramController::printElapsedIterations, this);
    std::string seed;

    _dbCtrl.loadAllValues(lang);

    while (!_success) {
        seed = createSeed(input, lang);

        if (findAutogram(seed, lang, input, pangrammode)) {
            _iterationsThread.detach();
            _success = true;
        }
    }

    _ioCtrl->printSucces(seed, _seconds, input);
}

bool Controllers::AutoGramController::findAutogram(std::string& seed, const Enums::LanguageEnum& lang, const std::string& input, bool pangrammode)
{
    int iterationCounter = 0;

    std::vector<std::pair<char, std::size_t>> oldAmounts = countSentence(seed, pangrammode);

    while (iterationCounter <= 10) {
        std::string result = createSentence(input, lang, oldAmounts);

        std::vector<std::pair<char, std::size_t>> newAmounts = countSentence(result, pangrammode);

        seed = result;
        if (oldAmounts == newAmounts) {            
            return true;
        }
        else {
            oldAmounts = newAmounts;
            ++iterationCounter;
        }
    }

    return false;
}

std::string Controllers::AutoGramController::createSentence(const std::string& input, const Enums::LanguageEnum& lang, const std::vector<std::pair<char, std::size_t>>& amounts)
{
    std::string retVal = input;

    for (std::pair<char, std::size_t> pair : amounts) {
        retVal.append(", " + _dbCtrl.getValue(lang, pair.second) + " " + pair.first + "'s");
    }

    retVal.append(".");

    return retVal;
}

std::string Controllers::AutoGramController::createSeed(const std::string& input, const Enums::LanguageEnum& lang)
{
    std::string retVal = input;

    try {
        for (int i{ 0 }; i < 5; ++i) {
            retVal.append(" " + _dbCtrl.getValue(lang, _dist(_random->getInstance())));
        }
    }
    catch (std::exception e) {
        throw std::runtime_error("Cannot retrieve numbers from database class");
    }

    return retVal;
}

std::vector<std::pair<char, std::size_t>> Controllers::AutoGramController::countSentence(const std::string& value, bool pangrammode)
{
    std::vector<std::pair<char, std::size_t>> temp = {};

    for (char p : _letters) {
        std::size_t amount = std::count(value.begin(), value.end(), p);

        if (amount > 0) {
            temp.push_back(std::pair<char, std::size_t>(p, amount));
        }
        else if (pangrammode) {
            temp.push_back(std::pair<char, std::size_t>(p, 1));
        }
    }

    ++_iterations;
    return temp;
}

void Controllers::AutoGramController::printElapsedIterations() {
    while (!_success) {
        sleep_for(1000ms);

        if (!_success) {
            std::cout << "Iterations per second: " << std::to_string(_iterations) << std::endl;
            _iterations = 0;
            ++_seconds;
        }
    }
}