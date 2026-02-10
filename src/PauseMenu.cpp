
#include "PauseMenu.h"

PauseMenu::PauseMenu(float height, float windowWidth, float windowHeight):
    buttonSelected(-1),
    height(height),
    font("rsrc/Fonts/Arial.ttf"),
    title(font, "Game is Paused", 35),
    itemsText{
        sf::Text(font, "Resume Game", 22),
        sf::Text(font, "Back to Menu", 22),
    },
    itemsButtons{
        sf::RectangleShape({300.f, 50.f}),
        sf::RectangleShape({300.f, 50.f})
    },
    blackBackground({windowWidth, windowHeight}),
    background({windowWidth, height})
{
    blackBackground.setFillColor(sf::Color(0,0,0,180));

    background.setFillColor(sf::Color(30, 50, 70));
    background.setOrigin(background.getGlobalBounds().getCenter());
    background.setPosition(sf::Vector2f(windowWidth/2, windowHeight/2));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(3);

    title.setOrigin(title.getGlobalBounds().getCenter());
    title.setPosition({windowWidth/2, background.getPosition().y - 50});

    for (int i = 0; i < 2; ++i) {
        itemsText[i].setOrigin(itemsText[i].getGlobalBounds().getCenter());
        itemsText[i].setFillColor(sf::Color::White);
        itemsText[i].setPosition({windowWidth/2 - 200 + 400 * i, background.getPosition().y + 60});

        itemsButtons[i].setOrigin(itemsButtons[i].getGlobalBounds().getCenter());
        itemsButtons[i].setFillColor(sf::Color(30, 50, 70));
        itemsButtons[i].setOutlineColor(sf::Color::White);
        itemsButtons[i].setOutlineThickness(2);
        itemsButtons[i].setPosition(itemsText[i].getPosition());
    }
}

auto PauseMenu::draw(sf::RenderWindow &window) const -> void {
    window.draw(blackBackground);
    window.draw(background);
    for (int i = 0; i < 2; ++i) {
        window.draw(itemsButtons[i]);
        window.draw(itemsText[i]);
    }
    window.draw(title);
}

auto PauseMenu::selectItem() -> void {
    for (int i = 0; i < 2; ++i) {
        if (buttonSelected == i) {
            itemsButtons[i].setFillColor(sf::Color::White);
            itemsText[i].setFillColor(sf::Color(30, 50, 70));
        } else {
            itemsButtons[i].setFillColor(sf::Color(30, 50, 70));
            itemsText[i].setFillColor(sf::Color::White);
        }
    }
}

auto PauseMenu::moveLeft() -> void {
    if (buttonSelected < 0)
        buttonSelected = 0;
    else if (buttonSelected - 1 >= 0)
        buttonSelected--;
    else if (buttonSelected == 0)
        buttonSelected = 2 - 1;
    selectItem();
}

auto PauseMenu::moveRight() -> void {
    if (buttonSelected < 0)
        buttonSelected = 1;
    else if (buttonSelected + 1 < 2)
        buttonSelected++;
    else if (buttonSelected == 2 - 1)
        buttonSelected = 0;
    selectItem();
}

auto PauseMenu::unSelectItem() -> void {
    for (int i = 0; i < 2; ++i) {
        itemsButtons[i].setFillColor(sf::Color(30, 50, 70));
        itemsText[i].setFillColor(sf::Color::White);
    }
    buttonSelected = -1;
}
