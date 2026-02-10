#ifndef QUITMENU_H
#define QUITMENU_H
#pragma once

#include "SFML/Graphics.hpp"
#define MAX_QUIT_OPTIONS 2

class QuitMenu {
    int buttonSelected;
    sf::Font font;
    sf::Text title;
    float height;
    sf::Text optionsText[MAX_QUIT_OPTIONS];
    sf::RectangleShape optionsButtons[MAX_QUIT_OPTIONS]{
        sf::RectangleShape({300.f, 50.f}),
        sf::RectangleShape({300.f, 50.f})
    };
    sf::RectangleShape blackBackground;
    sf::RectangleShape background;

public:
    QuitMenu(float height, sf::RenderWindow& window);
    auto draw(sf::RenderWindow& window) const -> void;
    auto moveLeft() -> void;
    auto moveRight() -> void;
    auto selectItem() -> void;
    int getSelectedItem() const {
        return buttonSelected;
    }
    auto unSelectItem() -> void;

};



#endif //QUITMENU_H
