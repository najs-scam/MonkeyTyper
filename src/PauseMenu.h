//
// Created by szgod on 02.05.2025.
//

#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#pragma once

#include "SFML/Graphics.hpp"
#include <vector>

class PauseMenu {
    int buttonSelected;
    sf::Font font;
    sf::Text title;
    float height;
    std::vector<sf::Text> itemsText;
    std::vector<sf::RectangleShape> itemsButtons;
    sf::RectangleShape blackBackground;
    sf::RectangleShape background;
public:
    PauseMenu(float height,  float windowWidth, float windowHeight);
    auto draw(sf::RenderWindow& window) const -> void;
    auto moveLeft() -> void;
    auto moveRight() -> void;
    auto selectItem() -> void;
    auto getSelectedItem() const -> int {
        return buttonSelected;
    }
    auto unSelectItem() -> void;

};



#endif //PAUSEMENU_H
