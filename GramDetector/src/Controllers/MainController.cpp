#include "MainController.h"
#include <sqlite3.h> 
#include <iostream>
#include <filesystem>
#include "../Enums/LanguageEnum.h"
#include "../Enums/TypeEnum.h"
#include "IOController.h"

using namespace GramDetector;

Controllers::MainController::MainController() : _autogramCtrl{ _randomEngine, _ioCtrl }, _randomEngine{ std::make_shared<Models::RandomEngine>() } {}

void Controllers::MainController::run()
{
    Enums::TypeEnum type = getGramType();
    Enums::LanguageEnum lang = getLanguage();

    if (type == Enums::TypeEnum::AUTOGRAM)
        _autogramCtrl.start(_ioCtrl->getSentence(), lang, false);
    else if (type == Enums::TypeEnum::PANGRAM)
        _autogramCtrl.start(_ioCtrl->getSentence(), lang, true);
}

const Enums::TypeEnum Controllers::MainController::getGramType() const
{
    GramDetector::Enums::TypeEnum retVal;

    switch (_ioCtrl->getGramType()) {
    case 1:
        retVal = GramDetector::Enums::TypeEnum::PANGRAM;
        break;
    default:
        retVal = GramDetector::Enums::TypeEnum::AUTOGRAM;
        break;
    }

    return retVal;
}

const Enums::LanguageEnum Controllers::MainController::getLanguage() const
{
    GramDetector::Enums::LanguageEnum retVal;

    switch (_ioCtrl->getLangType()) {
    case 1:
        retVal = GramDetector::Enums::LanguageEnum::EN;
        break;
    default:
        retVal = GramDetector::Enums::LanguageEnum::NL;
        break;
    }

    return retVal;
}