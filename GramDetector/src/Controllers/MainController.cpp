#include "MainController.h"
#include <sqlite3.h> 
#include <iostream>
#include <filesystem>
#include "../Enums/LanguageEnum.h"

GramDetector::Controllers::MainController::MainController() : _autogramCtrl{ _randomEngine }, _randomEngine{ std::make_shared<Models::RandomEngine>() } {}

const GramDetector::Enums::TypeEnum GramDetector::Controllers::MainController::getGramType() const
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

const GramDetector::Enums::LanguageEnum GramDetector::Controllers::MainController::getLanguage() const
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

void GramDetector::Controllers::MainController::run()
{
    GramDetector::Enums::TypeEnum type = getGramType();
    GramDetector::Enums::LanguageEnum lang = getLanguage();
    std::string sentence = _input.getSentence();

    if (type == Enums::TypeEnum::AUTOGRAM)
        _autogramCtrl.start(sentence, lang);
    else if (type == Enums::TypeEnum::PANGRAM)
        _autogramCtrl.start(sentence, lang);
}