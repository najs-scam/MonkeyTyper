//
// Created by szgod on 27.04.2025.
//

#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Difficulty.h"

#define MAX_SETTING_ITEMS 5

class SettingsMenu {
public:
    SettingsMenu(float width, float height);
    auto moveUp() -> void;
    auto moveDown() -> void;
    auto moveLeft() -> void;
    auto moveRight() -> void;
    auto selectItem() -> void;

    static auto setObjectProperties(sf::Text& text, sf::RectangleShape& background,
                                    float xPos, float yPos) -> void;

    auto draw(sf::RenderWindow& window) -> void;
    auto saveFont() -> std::string;
    auto saveDifficulty() -> Difficulty;
    auto saveFontColor() -> std::vector<sf::Color>;
    auto saveHudColor() -> std::vector<sf::Color>;
    auto saveWordSize() -> int;

private:
    int settingSelected;
    sf::Font font;
    std::vector<sf::Text> settingsNames;
    std::vector<sf::RectangleShape> setNamesBackgrounds;

    std::vector<sf::Text> settings;
    std::vector<sf::RectangleShape> settings_backgrounds;

    std::vector<bool> settings_Selected;

    std::vector<std::string> fontPaths;
    std::vector<std::string> fontNames;

    std::vector<Difficulty> difficultyModes;
    std::vector<std::string> difficultyNames;

    std::vector<std::vector<sf::Color>> fontColorModes;
    std::vector<std::string> fontColorNames;

    std::vector<std::vector<sf::Color>> hudBarColorModes;
    std::vector<std::string> hudBarColorNames;

    std::vector<int> wordsSize;
    std::vector<std::string> wordSizeNames;

    std::vector<int> changeSettingSelected;

    std::map<std::string, std::string> keyBindings;
    int fontSize;

};



#endif //SETTINGSMENU_H
