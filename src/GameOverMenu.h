//
// Created by szgod on 02.05.2025.
//

#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#pragma once

#include "SFML/Graphics.hpp"
#include "StatsObject.h"
#include <vector>

class GameOverMenu {
    int buttonSelected;
    sf::Font font;
    sf::Text title;
    const float height = 480;
    const float width = 900;
    std::vector<sf::Text> itemsText;
    std::vector<sf::RectangleShape> itemsButtons;
    sf::RectangleShape blackBackground;
    sf::RectangleShape background;
    StatsObject statsObj;
    std::vector<sf::Text> statsText;

public:
    GameOverMenu(float windowWidth, float windowHeight);
    auto draw(sf::RenderWindow& window) -> void;
    auto moveLeft() -> void;
    auto moveRight() -> void;
    auto selectItem() -> void;
    int getSelectedItem() const {
        return buttonSelected;
    }
    auto unSelectItem() -> void;
    auto setStats(const StatsObject &statsObj) -> void;
    auto getStats() -> StatsObject;
    auto updateStats() -> void;
};



#endif //GAMEOVERMENU_H
