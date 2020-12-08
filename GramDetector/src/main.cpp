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
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

        GramDetector::Controllers::MainController ctrl;
        ctrl.run();
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}
