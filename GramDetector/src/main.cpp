#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <iostream>
#include <random>
#include "Models/RandomEngine.h"
#include "./Controllers/MainController.h"

int main()
{
    try {


        GramDetector::Controllers::MainController ctrl;
        GramDetector::Models::RandomEngine* eng = {new GramDetector::Models::RandomEngine() };

        ctrl.run();

        _CrtDumpMemoryLeaks();

    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}
