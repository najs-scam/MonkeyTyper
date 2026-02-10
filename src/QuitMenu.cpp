
#include "QuitMenu.h"

QuitMenu::QuitMenu(float height, sf::RenderWindow& window) :
    font("rsrc/Fonts/Arial.ttf"),
    title(font, "Are You Sure?", 35),
    optionsText{
        sf::Text(font, "Yes, I am a Coward", 22),
        sf::Text(font, "No, I never Surrender", 22),
    }
{
    this->height = height;
    blackBackground.setSize(sf::Vector2f(window.getSize()));
    blackBackground.setFillColor(sf::Color(0, 0, 0, 180));

    background.setSize({static_cast<float>(window.getSize().x + 200), height});
    background.setFillColor(sf::Color(sf::Color(30, 50, 70)));
    background.setPosition({
        window.getSize().x / 2.f - background.getSize().x / 2.f,
        window.getSize().y / 2.f - height / 2.f
    });
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(3);
    title.setOrigin(title.getGlobalBounds().getCenter());
    title.setPosition({static_cast<float>(window.getSize().x /2), background.getPosition().y + 60});

    optionsText[0].setOrigin(optionsText[0].getGlobalBounds().getCenter());
    optionsText[0].setFillColor(sf::Color::White);
    optionsText[0].setPosition({static_cast<float>(window.getSize().x /2) - 200 , background.getPosition().y + 170});

    optionsText[1].setOrigin(optionsText[1].getGlobalBounds().getCenter());
    optionsText[1].setFillColor(sf::Color::White);
    optionsText[1].setPosition({static_cast<float>(window.getSize().x /2) + 200 , background.getPosition().y + 170});

    optionsButtons[0].setFillColor(sf::Color(30, 50, 70));
    optionsButtons[0].setOutlineColor(sf::Color::White);
    optionsButtons[0].setOutlineThickness(2);
    optionsButtons[0].setOrigin(optionsButtons[0].getGlobalBounds().getCenter());
    optionsButtons[0].setPosition(optionsText[0].getPosition());

    optionsButtons[1].setFillColor(sf::Color(sf::Color(30, 50, 70)));
    optionsButtons[1].setOutlineColor(sf::Color::White);
    optionsButtons[1].setOutlineThickness(2);
    optionsButtons[1].setOrigin(optionsButtons[1].getGlobalBounds().getCenter());
    optionsButtons[1].setPosition(optionsText[1].getPosition());

    buttonSelected = -1;
}

auto QuitMenu::draw(sf::RenderWindow &window) const -> void {
    window.draw(blackBackground);
    window.draw(background);
    for (int i = 0; i < MAX_QUIT_OPTIONS; i++) {
        window.draw(optionsButtons[i]);
        window.draw(optionsText[i]);
    }
    window.draw(title);
}

auto QuitMenu::moveLeft() -> void {
    if (buttonSelected == -1) {
        buttonSelected = 0;
    } else
    if (buttonSelected - 1 >= 0)
        buttonSelected--;
    else if (buttonSelected == 0)
        buttonSelected = MAX_QUIT_OPTIONS - 1;
    selectItem();
}

auto QuitMenu::moveRight() -> void {
    if (buttonSelected == -1)
        buttonSelected = 1;
    else if (buttonSelected + 1 < MAX_QUIT_OPTIONS)
        buttonSelected++;
    else if (buttonSelected == MAX_QUIT_OPTIONS - 1)
        buttonSelected = 0;
    selectItem();
}

auto QuitMenu::selectItem() -> void {
    for (int i = 0; i < MAX_QUIT_OPTIONS; i++) {
        if (buttonSelected == i) {
            optionsButtons[i].setFillColor(sf::Color::White);
            optionsText[i].setFillColor(sf::Color::Black);
        } else {
            optionsButtons[i].setFillColor(sf::Color(30, 50, 70));
            optionsText[i].setFillColor(sf::Color::White);
        }
    }
}

auto QuitMenu::unSelectItem() -> void {
    for (int i = 0; i < MAX_QUIT_OPTIONS; i++) {
        optionsButtons[i].setFillColor(sf::Color(30, 50, 70));
        optionsText[i].setFillColor(sf::Color::White);
    }
    buttonSelected = -1;
}


