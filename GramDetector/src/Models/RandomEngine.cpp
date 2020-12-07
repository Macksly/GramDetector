#include "RandomEngine.h"

std::default_random_engine& GramDetector::Models::RandomEngine::getInstance()
{
    return dre;
}