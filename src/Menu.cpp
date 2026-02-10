#include "Menu.h"

Menu::Menu(float x, float y):
    font("rsrc/Fonts/Arial.ttf"),
    menuItems{
        sf::Text(font, "Play", 40),
        sf::Text(font, "Load", 40),
        sf::Text(font, "Settings", 40),
        sf::Text(font, "Quit", 40),
    },
    title(font, "Monkey Typer", 60),
    menuButtons{
        sf::RectangleShape({x/6, 70}),
        sf::RectangleShape({x/6, 70}),
        sf::RectangleShape({x/6, 70}),
        sf::RectangleShape({x/6, 70}),
    }
{
    //TITLE
    title.setOrigin(title.getGlobalBounds().getCenter());
    title.setPosition({x / 2, 180});

    titleBackground.setSize({x/3, 150});
    titleBackground.setFillColor(sf::Color::Blue);
    titleBackground.setOutlineColor(sf::Color::White);
    titleBackground.setOutlineThickness(2);
    titleBackground.setOrigin(titleBackground.getGlobalBounds().getCenter());
    titleBackground.setPosition(title.getPosition());

    //PLAY
    menuItems[0].setOrigin(menuItems[0].getGlobalBounds().getCenter());
    menuItems[0].setFillColor(sf::Color::White);
    menuItems[0].setPosition({x / 2, 350});

    menuButtons[0].setFillColor(sf::Color::Blue);
    menuButtons[0].setOutlineColor(sf::Color::White);
    menuButtons[0].setOutlineThickness(2);
    menuButtons[0].setOrigin(menuButtons[0].getGlobalBounds().getCenter());
    menuButtons[0].setPosition(menuItems[0].getPosition());

    //SCORE BOARD
    menuItems[1].setOrigin(menuItems[1].getGlobalBounds().getCenter());
    menuItems[1].setFillColor(sf::Color::White);
    menuItems[1].setPosition({x / 2, 450});

    menuButtons[1].setFillColor(sf::Color::Blue);
    menuButtons[1].setOutlineColor(sf::Color::White);
    menuButtons[1].setOutlineThickness(2);
    menuButtons[1].setOrigin(menuButtons[1].getGlobalBounds().getCenter());
    menuButtons[1].setPosition(menuItems[1].getPosition());

    //SETTINGS
    menuItems[2].setOrigin(menuItems[2].getGlobalBounds().getCenter());
    menuItems[2].setFillColor(sf::Color::White);
    menuItems[2].setPosition({x / 2, 550});

    menuButtons[2].setFillColor(sf::Color::Blue);
    menuButtons[2].setOutlineColor(sf::Color::White);
    menuButtons[2].setOutlineThickness(2);
    menuButtons[2].setOrigin(menuButtons[2].getGlobalBounds().getCenter());
    menuButtons[2].setPosition(menuItems[2].getPosition());

    //QUIT
    menuItems[3].setOrigin(menuItems[3].getGlobalBounds().getCenter());
    menuItems[3].setFillColor(sf::Color::White);
    menuItems[3].setPosition({x / 2, 650});

    menuButtons[3].setFillColor(sf::Color::Blue);
    menuButtons[3].setOutlineColor(sf::Color::White);
    menuButtons[3].setOutlineThickness(2);
    menuButtons[3].setOrigin(menuButtons[3].getGlobalBounds().getCenter());
    menuButtons[3].setPosition(menuItems[3].getPosition());


    menuSelected = -1;
}


void Menu::draw(sf::RenderWindow& window) const {
    window.draw(titleBackground);
    window.draw(title);
    for (int i = 0; i < MAX_MENU_ITEMS; i++) {
        window.draw(menuButtons[i]);
        window.draw(menuItems[i]);
    }
}

auto Menu::moveUp() -> void {
    if (menuSelected == -1)
        menuSelected = 1;
    if (menuSelected - 1 >= 0)
        menuSelected--;
    else if (menuSelected == 0)
        menuSelected = MAX_MENU_ITEMS - 1;
    selectItem();
}

auto Menu::moveDown() -> void {
    if (menuSelected + 1 < MAX_MENU_ITEMS)
        menuSelected++;
    else if (menuSelected == MAX_MENU_ITEMS - 1)
        menuSelected = 0;
    selectItem();
}

auto Menu::selectItem() -> void {
    for (int i = 0; i < MAX_MENU_ITEMS; i++) {
        if (menuSelected == i) {
            menuItems[i].setFillColor(sf::Color::Black);
            menuButtons[i].setFillColor(sf::Color::White);
        } else {
            menuItems[i].setFillColor(sf::Color::White);
            menuButtons[i].setFillColor(sf::Color::Blue);
        }
    }
}

auto Menu::unSelectItem() -> void {
    for (int i = 0; i < MAX_MENU_ITEMS; i++) {
        menuItems[i].setFillColor(sf::Color::White);
        menuButtons[i].setFillColor(sf::Color::Blue);
    }
    menuSelected = -1;
}




