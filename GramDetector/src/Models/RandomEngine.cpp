#include "RandomEngine.h"

using namespace GramDetector;

Models::RandomEngine::RandomEngine() : _dre{dev()} {}

std::default_random_engine& Models::RandomEngine::getInstance()
{
    return _dre;
}