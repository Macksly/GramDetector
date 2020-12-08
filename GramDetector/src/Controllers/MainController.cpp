#include "MainController.h"
#include <sqlite3.h> 
#include <iostream>
#include <filesystem>
#include "../Enums/LanguageEnum.h"


GramDetector::Enums::TypeEnum GramDetector::Controllers::MainController::getGramType()
{
    GramDetector::Enums::TypeEnum retVal;

    switch (_input.getGramType()) {
    case 1:
        retVal = GramDetector::Enums::TypeEnum::PANGRAM;
        break;
    default:
        retVal = GramDetector::Enums::TypeEnum::AUTOGRAM;
        break;
    }

    return retVal;
}

GramDetector::Enums::LanguageEnum GramDetector::Controllers::MainController::getLanguage()
{
    GramDetector::Enums::LanguageEnum retVal;

    switch (_input.getLangType()) {
    case 1:
        retVal = GramDetector::Enums::LanguageEnum::EN;
        break;
    default:
        retVal = GramDetector::Enums::LanguageEnum::NL;
        break;
    }

    return retVal;
}

GramDetector::Controllers::MainController::MainController()
{
    _randomEngine = std::make_shared<Models::RandomEngine>();

    _autogramCtrl = std::make_unique<Controllers::AutoGramController>(_randomEngine);
}

void GramDetector::Controllers::MainController::run()
{
    GramDetector::Enums::TypeEnum type = getGramType();
    GramDetector::Enums::LanguageEnum lang = getLanguage();

    if (type == Enums::TypeEnum::AUTOGRAM)
        _autogramCtrl->start(_input.getSentence(), lang);
    else if (type == Enums::TypeEnum::PANGRAM)
        _autogramCtrl->start(_input.getSentence(), lang);
}