
#include "GameOverMenu.h"
#include <string>
#include <sstream>
#include <format>

GameOverMenu::GameOverMenu(float windowWidth, float windowHeight):
    buttonSelected(-1),
    font("rsrc/Fonts/Arial.ttf"),
    title(font, "Game Over", 60),
    itemsText{
        sf::Text(font, "Save Score", 30),
        sf::Text(font, "Don't Save", 30),
    },
    itemsButtons{
        sf::RectangleShape({300.f, 70.f}),
        sf::RectangleShape({300.f, 70.f})
    },
    blackBackground({windowWidth, windowHeight}),
    background({width, height}),
    statsObj(0,0,0,0,0,Difficulty::NORMAL),
    statsText{
        sf::Text(font,
            [](int min, int sec) {
                std::stringstream ss;
                ss << "Time: " << std::setw(2) << std::setfill('0') << min << ":"
                    << std::setw(2) << std::setfill('0') << sec;
                return ss.str();
            } (statsObj.minutes, statsObj.seconds),
            23
            ),
        sf::Text(font, "Score: " + std::to_string(statsObj.score) ,23),
        sf::Text(font, "Total Words: " + std::to_string(statsObj.totalWords) ,23),
        sf::Text(font, std::format("Words/Minutes: {:.2}",statsObj.wordsPerMinute),23),
        sf::Text(font, "Mode: NORMAL",23),
    }
{
    blackBackground.setFillColor(sf::Color(0,0,0,140));
    background.setFillColor(sf::Color(30, 50, 70));
    background.setOrigin(background.getGlobalBounds().getCenter());
    background.setPosition({windowWidth/2, windowHeight/2});
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(3);

    title.setOrigin(title.getGlobalBounds().getCenter());
    title.setPosition({windowWidth/2, background.getPosition().y - 120});

    for (int i = 0; i < 2; ++i) {
        itemsText[i].setOrigin(itemsText[i].getGlobalBounds().getCenter());
        itemsText[i].setFillColor(sf::Color::White);
        itemsText[i].setPosition({windowWidth/2 - 200 + 400 * i, background.getPosition().y + 100});

        itemsButtons[i].setOrigin(itemsButtons[i].getGlobalBounds().getCenter());
        itemsButtons[i].setFillColor(sf::Color(30, 50, 70));
        itemsButtons[i].setOutlineColor(sf::Color::White);
        itemsButtons[i].setOutlineThickness(2);
        itemsButtons[i].setPosition(itemsText[i].getPosition());
    }
    for (int i = 0; i < statsText.size(); ++i) {
        if (i < 3) {
            statsText[i].setOrigin(statsText[i].getGlobalBounds().getCenter());
            statsText[i].setFillColor(sf::Color::White);
            statsText[i].setPosition({windowWidth/2 - 200 + 200 * i , background.getPosition().y - 40});
        } else {
            statsText[i].setOrigin(statsText[i].getGlobalBounds().getCenter());
            statsText[i].setFillColor(sf::Color::White);
            statsText[i].setPosition({windowWidth/2 - 700 + 200 * i , background.getPosition().y + 10});
        }
    }
}

auto GameOverMenu::draw(sf::RenderWindow &window) -> void {
    window.draw(blackBackground);
    window.draw(background);
    for (int i = 0; i < 2; ++i) {
        window.draw(itemsButtons[i]);
        window.draw(itemsText[i]);
    }
    for (int i = 0; i < statsText.size(); ++i) {
        window.draw(statsText[i]);
    }
    window.draw(title);
}

auto GameOverMenu::selectItem() -> void {
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

auto GameOverMenu::moveLeft() -> void {
    if (buttonSelected < 0)
        buttonSelected = 0;
    else if (buttonSelected - 1 >= 0)
        buttonSelected--;
    else if (buttonSelected == 0)
        buttonSelected = 2 - 1;
    selectItem();
}

auto GameOverMenu::moveRight() -> void {
    if (buttonSelected < 0)
        buttonSelected = 1;
    else if (buttonSelected + 1 < 2)
        buttonSelected++;
    else if (buttonSelected == 2 - 1)
        buttonSelected = 0;
    selectItem();
}

auto GameOverMenu::unSelectItem() -> void {
    for (int i = 0; i < 2; ++i) {
        itemsButtons[i].setFillColor(sf::Color(30, 50, 70));
        itemsText[i].setFillColor(sf::Color::White);
    }
    buttonSelected = -1;
}

auto GameOverMenu::setStats(const StatsObject &statsObjCop) -> void {
    statsObj = statsObjCop;
    updateStats();
}

auto GameOverMenu::getStats() -> StatsObject {
    return statsObj;
}

auto GameOverMenu::updateStats() -> void {
    auto time = std::stringstream();
    time << std::setw(2) << std::setfill('0') << statsObj.minutes << ":"
        << std::setw(2) << std::setfill('0') << statsObj.seconds;
    statsText[0].setString("Time: " + time.str());

    statsText[1].setString("Score: " + std::to_string(statsObj.score));
    statsText[2].setString("Total Words: " + std::to_string(statsObj.totalWords));
    statsText[3].setString(std::format("W/M: {:.3f}", statsObj.wordsPerMinute));
    auto difficultyStr = std::string();
    switch (statsObj.difficulty) {
        case Difficulty::EASY: difficultyStr = "EASY"; break;
        case Difficulty::NORMAL: difficultyStr = "NORMAL"; break;
        case Difficulty::HARD: difficultyStr = "HARD"; break;
    }
    statsText[4].setString("Mode: " + difficultyStr);
}
