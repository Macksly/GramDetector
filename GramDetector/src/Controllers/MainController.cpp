#include "MainController.h"
#include <sqlite3.h> 
#include <iostream>
#include <filesystem>
#include "../Enums/LanguageEnum.h"


GramDetector::Enums::TypeEnum GramDetector::Controllers::MainController::getGramType()
{
    switch (_input.getGramType()) {
    case 0:
        return GramDetector::Enums::TypeEnum::PANGRAM;
    case 1:
        return GramDetector::Enums::TypeEnum::AUTOGRAM;
    }
}

GramDetector::Enums::LanguageEnum GramDetector::Controllers::MainController::getLanguage()
{
    switch (_input.getLangType()) {
    case 1:
        return GramDetector::Enums::LanguageEnum::EN;
    default:
        return GramDetector::Enums::LanguageEnum::NL;
    }
}

GramDetector::Controllers::MainController::MainController()
{
    _randomEngine.reset(new Models::RandomEngine);


    _autogramCtrl.reset(new AutoGramController{ _randomEngine });
}

void GramDetector::Controllers::MainController::run()
{
    GramDetector::Enums::TypeEnum type = getGramType();
    GramDetector::Enums::LanguageEnum lang = getLanguage();

    if (type == Enums::TypeEnum::AUTOGRAM)
        _autogramCtrl->start(_input.getSentence(), lang);
}