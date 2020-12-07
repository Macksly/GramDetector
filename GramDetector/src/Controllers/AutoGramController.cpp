#include "AutoGramController.h"
#include <iostream>
#include <chrono>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std::this_thread;
using namespace std::chrono_literals;

GramDetector::Controllers::AutoGramController::AutoGramController(std::shared_ptr<GramDetector::Models::RandomEngine> random) : _random{ random }, _iterations{ 0 }, _succes{false}
{
    _letters = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
}

bool GramDetector::Controllers::AutoGramController::start(std::string input, GramDetector::Enums::LanguageEnum lang)
{
    _input = input.append(",");
    int seedCounter = 1;
    std::uniform_int_distribution<int> dist{ 1, 200 };

    bool succes = false;
    _lang = lang;
    
    _iterationsThread = std::thread(&GramDetector::Controllers::AutoGramController::printElapsedIterations, this);

    while (!_succes) {
        std::string seed = _input;
        for (int i{ 0 }; i < 2; ++i) {
            seed.append(" " + _dbCtrl.getValue(_lang, dist(_random->getInstance())));
        }

        std::cout << "New Seed Created (Nr: " << seedCounter << ")" << _input << std::endl;

        if (findAutogram(_input)) {
            _succes = true;
        }
        else {
            ++seedCounter;
        }
    }
    return true;
}

void GramDetector::Controllers::AutoGramController::printElapsedIterations() {
    while (!_succes) {
        sleep_for(1000ms);
        std::cout << "Iterations per second: " << std::to_string(_iterations) << std::endl;
        _iterations = 0;
    }
}

bool GramDetector::Controllers::AutoGramController::findAutogram(std::string& seed)
{
    int iterationCounter = 0;

    while (iterationCounter <= 100) {
        std::vector<std::pair<char, std::size_t>> oldAmounts = countSentence(seed);

        std::string result = createSentence(seed, oldAmounts);

        std::vector<std::pair<char, std::size_t>> newAmounts = countSentence(result);

        if (oldAmounts == newAmounts) {
            std::cout << "Autogram found at iteration " << iterationCounter << ": " << result << std::endl;
            return true;
        }
        else {
            seed = result;
            ++iterationCounter;
        }
        _iterationsThread.detach();
        return true;
    }

    return true;
}

std::string GramDetector::Controllers::AutoGramController::createSentence(const std::string& seed, const std::vector<std::pair<char, std::size_t>>& amounts)
{
    std::string retVal = _input;
    for (std::pair<char, std::size_t> pair : amounts) {
        retVal.append(" " + _dbCtrl.getValue(_lang, pair.second) + " " + pair.first + "'s,");
    }

    return retVal;
}

std::vector<std::pair<char, std::size_t>> GramDetector::Controllers::AutoGramController::countSentence(const std::string& seed)
{
    std::vector<std::pair<char, std::size_t>> temp = {};

    for (char p : _letters) {
        std::size_t amount = std::count(seed.begin(), seed.end(), p);

        if (amount > 0) {
            temp.push_back(std::pair<char, std::size_t>(p, amount));
        }
        else {
            temp.push_back(std::pair<char, std::size_t>(p, 1));
        }
    }

    ++_iterations;
    return temp;
}