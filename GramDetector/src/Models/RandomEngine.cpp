#include "RandomEngine.h"

GramDetector::Models::RandomEngine::RandomEngine() : _dre{dev()} {}

std::default_random_engine& GramDetector::Models::RandomEngine::getInstance()
{
    return _dre;
}