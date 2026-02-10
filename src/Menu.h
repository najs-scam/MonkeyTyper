#ifndef MENU_H
#define MENU_H
#pragma once
#include "SFML/Graphics.hpp"

#define MAX_MENU_ITEMS 4
class Menu {
public:

    Menu(float x, float y);
    auto draw(sf::RenderWindow& window) const -> void;
    auto moveUp() -> void;
    auto moveDown() -> void;
    auto selectItem() -> void;
    auto unSelectItem() -> void;
    int getSelectedItem() const {
        return menuSelected;
    }

private:
    int menuSelected;
    sf::Font font;
    sf::Text menuItems[MAX_MENU_ITEMS];
    sf::RectangleShape menuButtons[MAX_MENU_ITEMS];
    sf::Text title;
    sf::RectangleShape titleBackground;
};



#endif //MENU_H
