
#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(float width, float height):
    font("rsrc/Fonts/Arial.ttf"),
    settingsNames{
        sf::Text(font, "Change Font"),
        sf::Text(font, "Difficulty"),
        sf::Text(font, "Color of Words"),
        sf::Text(font, "Color of Hud"),
        sf::Text(font, "Words size"),
        sf::Text(font, "List of Key Binds"),
    },
    setNamesBackgrounds{
        sf::RectangleShape({width/6, 60}),
        sf::RectangleShape({width/6, 60}),
        sf::RectangleShape({width/6, 60}),
        sf::RectangleShape({width/6, 60}),
        sf::RectangleShape({width/6, 60}),
        sf::RectangleShape({width/6, 60}),
    },
    settings{
        sf::Text(font, "Arial"),
        sf::Text(font, "EASY"),
        sf::Text(font, "Classic"),
        sf::Text(font, "Storm"),
        sf::Text(font, "Medium"),
        sf::Text(font, "Check"),
    },
    settings_backgrounds{
        sf::RectangleShape({width/6, 60}),
        sf::RectangleShape({width/6, 60}),
        sf::RectangleShape({width/6, 60}),
        sf::RectangleShape({width/6, 60}),
        sf::RectangleShape({width/6, 60}),
        sf::RectangleShape({width/6, 60}),
    },
    settings_Selected{
        false, false, false, false, false, false
    }

{
    settingSelected = -1;
    //FONTS PATH
    fontPaths.emplace_back("rsrc/Fonts/Arial.ttf");
    fontPaths.emplace_back("rsrc/Fonts/BebasNeue-Regular.ttf");
    fontPaths.emplace_back("rsrc/Fonts/Blacknorthdemo-mLE25.otf");
    fontPaths.emplace_back("rsrc/Fonts/CrotahFreeVersionItalic-z8Ev3.ttf");
    fontPaths.emplace_back("rsrc/Fonts/SuperDream-ax3vE.ttf");

    fontNames.emplace_back("Arial");
    fontNames.emplace_back("Bebas Neue");
    fontNames.emplace_back("Black North");
    fontNames.emplace_back("Crotah");
    fontNames.emplace_back("Super Dream");


    //DIFFICULTY
    difficultyModes.emplace_back(Difficulty::EASY);
    difficultyModes.emplace_back(Difficulty::NORMAL);
    difficultyModes.emplace_back(Difficulty::HARD);

    difficultyNames.emplace_back("EASY");
    difficultyNames.emplace_back("NORMAL");
    difficultyNames.emplace_back("HARD");


    //FONT COLOR MODES
    fontColorModes.push_back({sf::Color::Green,sf::Color::Yellow,sf::Color::Red});
    fontColorModes.push_back({sf::Color(0, 255, 100),sf::Color(255, 80, 0),sf::Color(120, 0, 255)  });
    fontColorModes.push_back({sf::Color(0, 220, 255),sf::Color(255, 105, 180),sf::Color(173, 255, 47)});
    fontColorModes.push_back({sf::Color(255, 20, 147),sf::Color(0, 255, 255),sf::Color(255, 255, 0)});
    fontColorModes.push_back({sf::Color(255, 255, 0),sf::Color(255, 20, 147),sf::Color(50, 205, 50)});

    fontColorNames.emplace_back("Classic");
    fontColorNames.emplace_back("Neon");
    fontColorNames.emplace_back("Candy");
    fontColorNames.emplace_back("Pop");
    fontColorNames.emplace_back("Jungle");


    //HUB BAR COLOR MODE
    hudBarColorModes.push_back({sf::Color::White,sf::Color(30, 50, 70)});
    hudBarColorModes.push_back({sf::Color(0, 255, 255),sf::Color(48, 25, 52)});
    hudBarColorModes.push_back({sf::Color::White,sf::Color(120, 200, 210) });
    hudBarColorModes.push_back({sf::Color(255, 20, 147),sf::Color(25, 25, 112)});
    hudBarColorModes.push_back({sf::Color::Black, sf::Color(220, 220, 220)});

    hudBarColorNames.emplace_back("Storm");
    hudBarColorNames.emplace_back("Mystic");
    hudBarColorNames.emplace_back("Breeze");
    hudBarColorNames.emplace_back("Twilight");
    hudBarColorNames.emplace_back("Mono");


    //WORDS SIZE
    wordsSize.emplace_back(35); wordsSize.emplace_back(30); wordsSize.emplace_back(25);
    wordSizeNames.emplace_back("Large");
    wordSizeNames.emplace_back("Medium");
    wordSizeNames.emplace_back("Small");

    for (int i = 0; i < 4; i++)
        changeSettingSelected.emplace_back(0);
    changeSettingSelected.emplace_back(1);

    //KEY BINDS
    keyBindings["1Change Words Color"] = "CRLT + 1";
    keyBindings["2Change Hud Color"] =  "CRLT + 2";
    keyBindings["3Change Words Size"] ="CRLT + 3";

    for (int i = 0; i < 6; i++) {
        float yPos = i * 120.f + 150.f;
        setObjectProperties(settingsNames[i], setNamesBackgrounds[i], width / 5 * 2 - 100, yPos);
        setObjectProperties(settings[i], settings_backgrounds[i], width / 5 * 3 + 100, yPos);
    }


}

auto SettingsMenu::moveUp() -> void {
    if (settingSelected == -1)
        settingSelected = 1;
    if (settingSelected - 1 >= 0)
        settingSelected--;
    else if (settingSelected == 0)
        settingSelected = MAX_SETTING_ITEMS - 1;
    selectItem();
}

auto SettingsMenu::moveDown() -> void {
    if (settingSelected + 1 < MAX_SETTING_ITEMS)
        settingSelected++;
    else if (settingSelected == MAX_SETTING_ITEMS - 1)
        settingSelected = 0;
    selectItem();
}

auto SettingsMenu::moveLeft() -> void {
    if (settingSelected < 0 || settingSelected >= MAX_SETTING_ITEMS) return;

    switch (settingSelected) {
        case 0: // Change Font
            changeSettingSelected[0] = (changeSettingSelected[0] - 1 + fontNames.size()) % fontNames.size();
        settings[0].setString(fontNames[changeSettingSelected[0]]);
        break;

        case 1: // Difficulty
            changeSettingSelected[1] = (changeSettingSelected[1] - 1 + difficultyNames.size()) % difficultyNames.size();
        settings[1].setString(difficultyNames[changeSettingSelected[1]]);
        break;

        case 2: // Color of Words
            changeSettingSelected[2] = (changeSettingSelected[2] - 1 + fontColorNames.size()) % fontColorNames.size();
        settings[2].setString(fontColorNames[changeSettingSelected[2]]);
        break;

        case 3: // Color of Hud
            changeSettingSelected[3] = (changeSettingSelected[3] - 1 + hudBarColorNames.size()) % hudBarColorNames.size();
        settings[3].setString(hudBarColorNames[changeSettingSelected[3]]);
        break;

        case 4: // Words size
            changeSettingSelected[4] = (changeSettingSelected[4] - 1 + wordSizeNames.size()) % wordSizeNames.size();
        settings[4].setString(wordSizeNames[changeSettingSelected[4]]);
        break;
        default: ;
    }
}

auto SettingsMenu::moveRight() -> void {
    if (settingSelected < 0 || settingSelected >= MAX_SETTING_ITEMS) return;

    switch (settingSelected) {
        case 0: // Change Font
            changeSettingSelected[0] = (changeSettingSelected[0] + 1) % fontNames.size();
        settings[0].setString(fontNames[changeSettingSelected[0]]);
        break;

        case 1: // Difficulty
            changeSettingSelected[1] = (changeSettingSelected[1] + 1) % difficultyNames.size();
        settings[1].setString(difficultyNames[changeSettingSelected[1]]);
        break;

        case 2: // Color of Words
            changeSettingSelected[2] = (changeSettingSelected[2] + 1) % fontColorNames.size();
        settings[2].setString(fontColorNames[changeSettingSelected[2]]);
        break;

        case 3: // Color of Hud
            changeSettingSelected[3] = (changeSettingSelected[3] + 1) % hudBarColorNames.size();
        settings[3].setString(hudBarColorNames[changeSettingSelected[3]]);
        break;

        case 4: // Words size
            changeSettingSelected[4] = (changeSettingSelected[4] + 1) % wordSizeNames.size();
        settings[4].setString(wordSizeNames[changeSettingSelected[4]]);
        break;
        default: ;
    }
}

auto SettingsMenu::selectItem() -> void {
    for (int i = 0; i < MAX_SETTING_ITEMS; i++) {
        if (settingSelected == i) {
            settings[i].setFillColor(sf::Color::Black);
            settings_backgrounds[i].setFillColor(sf::Color::White);
            settings_Selected[i] = true;
        } else {
            settings[i].setFillColor(sf::Color::White);
            settings_backgrounds[i].setFillColor(sf::Color::Blue);
            settings_Selected[i] = false;
        }
    }
}

auto SettingsMenu::setObjectProperties(sf::Text &text, sf::RectangleShape &background, float xPos, float yPos) -> void {
    text.setCharacterSize(27);
    text.setOrigin(text.getGlobalBounds().getCenter());
    text.setPosition({xPos, yPos});
    background.setOrigin(background.getGlobalBounds().getCenter());
    background.setPosition({xPos, yPos});
    background.setFillColor(sf::Color::Blue);
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(1.5f);
}

auto SettingsMenu::draw(sf::RenderWindow &window) -> void {
    for (int i = 0; i < 5; i++) {
        window.draw(setNamesBackgrounds[i]);
        window.draw(settings_backgrounds[i]);
        window.draw(settings[i]);
        window.draw(settingsNames[i]);
    }
}

auto SettingsMenu::saveFont() -> std::string {
    return fontPaths[changeSettingSelected[0]];
}
auto SettingsMenu::saveDifficulty() -> Difficulty {
    return difficultyModes[changeSettingSelected[1]];
}
auto SettingsMenu::saveFontColor() -> std::vector<sf::Color> {
    return fontColorModes[changeSettingSelected[2]];
}
auto SettingsMenu::saveHudColor() -> std::vector<sf::Color> {
    return hudBarColorModes[changeSettingSelected[3]];
}
auto SettingsMenu::saveWordSize() -> int {
    return wordsSize[changeSettingSelected[4]];
}




