#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "GameState.h"
#include "Menu.h"
#include "PlayState.h"
#include "QuitMenu.h"
#include "PauseState.h"
#include "SettingsMenu.h"
#include "PauseMenu.h"
#include "GameOverMenu.h"
#include "TextBox.h"

auto main() -> int {

    constexpr int windowWidth = 1500, windowHeight = 800;

    auto window = sf::RenderWindow(
        sf::VideoMode({ windowWidth, windowHeight }),
        "Monkey Typer",
        sf::Style::Close,
        sf::State::Windowed,
        sf::ContextSettings{.antiAliasingLevel = 8}
    );
    window.setFramerateLimit(144);

    // MENU
    GameState currentState = GameState::MENU;
    Menu menu(windowWidth, windowHeight);
    auto font = sf::Font("rsrc/Fonts/Arial.ttf");
    auto title = sf::Text(font, "Monkey Typer", 40);

    //QUIT MENU
    QuitMenu quit_menu(250, window);

    //ACTUAL GAME
    PlayState playState(windowWidth, windowHeight);
    auto pauseState = PauseState::RUNNING;

    //GAME OVER
    GameOverMenu gameOverMenu(windowWidth, windowHeight);

    //PAUSE MENU
    PauseMenu pause_menu(250, windowWidth, windowHeight);

    //AUDIO
    auto buttonChangeBuffor = sf::SoundBuffer("rsrc/Audio/button-change.wav");
    auto buttonChangeSound = sf::Sound(buttonChangeBuffor);
    buttonChangeSound.setVolume(50);

    auto buttonEnterBuffor = sf::SoundBuffer("rsrc/Audio/button-enter.wav");
    auto buttonEnterSound = sf::Sound(buttonEnterBuffor);

    auto menuTheme = sf::Music("rsrc/Audio/menu-theme.wav");
    menuTheme.setVolume(25);

    auto gameTheme = sf::Music("rsrc/Audio/play-theme.wav");
    gameTheme.setVolume(20);

    //BACKGROUND
    auto backgroundTexture = sf::Texture();
    if (!backgroundTexture.loadFromFile("rsrc/Img/background.png"))
        return EXIT_FAILURE;

    auto backGround1 = sf::Sprite(backgroundTexture);
    auto backGround2 = sf::Sprite(backgroundTexture);
    backGround1.setPosition({0, 0});
    backGround2.setPosition({static_cast<float>(backgroundTexture.getSize().x), 0});
    auto backGroundSize = static_cast<float>(backgroundTexture.getSize().x);
    auto reset_Bg = sf::Vector2f({static_cast<float>(backgroundTexture.getSize().x)-10.f, 0});

    //TEXTBOX
    TextBox text_box(30, sf::Color::White, true, font);
    text_box.setLimit(true, 13);
    text_box.setSelected(true);
    text_box.setOriginCenter();
    text_box.setPosition({playState.getTextBoxBack().getPosition().x-120, windowHeight-35});
    auto input = std::string("");


    //SETTINGS
    SettingsMenu settingsMenu(windowWidth, windowHeight);

    auto gameFont = sf::Font("rsrc/Fonts/Arial.ttf");
    auto gameDifficulty = Difficulty::EASY;
    auto gameColor = std::vector{{sf::Color::Green,sf::Color::Yellow,sf::Color::Red}};
    auto gameHudColor = std::vector{{sf::Color::White,sf::Color(30, 50, 70)}};
    auto gameWordsSize = 30;
    //SETTINGS CODES
    text_box.setColor(sf::Color::White);

    sf::Clock clock;

    menuTheme.setLooping(true);
    menuTheme.play();
    gameTheme.setLooping(true);
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) window.close();
            switch (currentState) {
                case GameState::MENU:
                    window.clear();
                if (const auto key = event->getIf<sf::Event::KeyPressed>()) {
                    switch (key->code) {
                        case sf::Keyboard::Key::Up:
                            buttonChangeSound.play();
                            menu.moveUp();
                        break;
                        case sf::Keyboard::Key::Down:
                            buttonChangeSound.play();
                            menu.moveDown();
                        break;
                        case sf::Keyboard::Key::Enter:
                            buttonEnterSound.play();
                            switch (menu.getSelectedItem()) {
                                case 0:
                                    playState.resetGame();
                                    currentState = GameState::PLAY;
                                    clock.restart();
                                    menuTheme.stop();
                                    gameTheme.stop();
                                    gameTheme.play();
                                break;
                                case 1:
                                    currentState = GameState::PLAY;
                                    if (!clock.isRunning())
                                        clock.start();
                                    menuTheme.stop();
                                    gameTheme.play();
                                break;
                                case 2:
                                    currentState = GameState::SETTINGS;
                                break;
                                case 3:
                                    currentState = GameState::QUIT;
                                break;
                                default:
                                    window.clear();
                            }
                        menu.unSelectItem();
                        default:
                            break;
                    }
                }
                break;
                case GameState::PLAY:
                    switch (pauseState) {
                        case PauseState::RUNNING:
                            if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                                if (key->code == sf::Keyboard::Key::Escape) {
                                    buttonEnterSound.play();
                                    pauseState = PauseState::PAUSED;
                                    clock.stop();
                                }
                            }
                            if (playState.isWritingEnable)
                                if (const auto textEntered = event->getIf<sf::Event::TextEntered>()) {
                                    if (textEntered->unicode < 128) {
                                        text_box.typeOn(static_cast<char>(textEntered->unicode));
                                    }
                                    input = text_box.getInput();
                                    text_box.resetInput();
                                    if (playState.checkWordCompletion(input)) {
                                        playState.killWordByInput(input);
                                    }
                                }
                        break;
                        case PauseState::PAUSED:
                            gameTheme.pause();
                            if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                                switch (key->code) {
                                    case sf::Keyboard::Key::Escape:
                                        buttonEnterSound.play();
                                        gameTheme.play();
                                        pauseState = PauseState::RUNNING;
                                    break;
                                    case sf::Keyboard::Key::Left:
                                        buttonChangeSound.play();
                                        pause_menu.moveLeft();
                                    break;
                                    case sf::Keyboard::Key::Right:
                                        buttonChangeSound.play();
                                        pause_menu.moveRight();
                                    break;
                                    case sf::Keyboard::Key::Enter:
                                        buttonEnterSound.play();
                                        switch (pause_menu.getSelectedItem()) {
                                            case 0:
                                                pauseState = PauseState::RUNNING;
                                                gameTheme.play();
                                            break;
                                            case 1:
                                                pauseState = PauseState::RUNNING;
                                                currentState = GameState::MENU;
                                                clock.stop();
                                                menuTheme.play();
                                            break;
                                            default: ;
                                        }
                                    pause_menu.unSelectItem();
                                    break;
                                    default: ;
                                }
                            }
                            break;
                        case PauseState::GAMEOVER:
                            gameTheme.stop();
                            if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                                switch (key->code) {
                                    case sf::Keyboard::Key::Left:
                                        buttonChangeSound.play();
                                        gameOverMenu.moveLeft();
                                    break;
                                    case sf::Keyboard::Key::Right:
                                        buttonChangeSound.play();
                                        gameOverMenu.moveRight();
                                    break;
                                    case sf::Keyboard::Key::Enter:
                                        buttonEnterSound.play();
                                        switch (gameOverMenu.getSelectedItem()) {
                                            case 0:
                                            break;
                                            case 1:
                                                pauseState = PauseState::RUNNING;
                                                currentState = GameState::MENU;
                                                menuTheme.play();
                                            break;
                                            default: ;
                                        }
                                    gameOverMenu.unSelectItem();
                                    break;
                                    default: ;
                                }
                            }
                            break;
                    }

                break;
                case GameState::QUIT:
                    if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                        switch (key->code) {
                            case sf::Keyboard::Key::Left:
                                buttonChangeSound.play();
                                quit_menu.moveLeft();
                            break;
                            case sf::Keyboard::Key::Right:
                                buttonChangeSound.play();
                                quit_menu.moveRight();
                            break;
                            case sf::Keyboard::Key::Enter:
                                buttonEnterSound.play();
                                switch (quit_menu.getSelectedItem()) {
                                    case 0:
                                        window.close();
                                    break;
                                    case 1:
                                        currentState = GameState::MENU;
                                    break;
                                    default: ;
                                }
                            quit_menu.unSelectItem();
                            break;
                            default:
                                break;
                        }
                    }
                break;
                case GameState::SETTINGS:
                    if (const auto key = event->getIf<sf::Event::KeyPressed>()) {
                        if (key->code == sf::Keyboard::Key::Escape) {
                            buttonEnterSound.play();
                            currentState = GameState::MENU;
                        }
                        if (key->code == sf::Keyboard::Key::Up) {
                            buttonChangeSound.play();
                            settingsMenu.moveUp();
                        }
                        if (key->code == sf::Keyboard::Key::Down) {
                            buttonChangeSound.play();
                            settingsMenu.moveDown();
                        }
                        if (key->code == sf::Keyboard::Key::Left) {
                            buttonChangeSound.play();
                            settingsMenu.moveLeft();
                        }
                        if (key->code == sf::Keyboard::Key::Right) {
                            buttonChangeSound.play();
                            settingsMenu.moveRight();
                        }
                        if (key->code == sf::Keyboard::Key::Enter) {
                            buttonEnterSound.play();
                            gameFont = sf::Font(settingsMenu.saveFont());
                            gameDifficulty = settingsMenu.saveDifficulty();
                            gameColor = settingsMenu.saveFontColor();
                            gameHudColor = settingsMenu.saveHudColor();
                            gameWordsSize = settingsMenu.saveWordSize();
                            currentState = GameState::MENU;
                        }
                    }
                break;
                }

        }
        //LOGIKA GRY
        if (currentState == GameState::PLAY && pauseState == PauseState::RUNNING) {
            if (!clock.isRunning())
                clock.start();
            sf::Time elapsed = clock.getElapsedTime();
            float deltaTime = elapsed.asSeconds();
            playState.updateStats(deltaTime);
            playState.GamePlay(deltaTime);
            if (playState.gameOver()) {
                gameOverMenu.setStats(playState.getPlayerStatistics());
                playState.resetGame();
                pauseState = PauseState::GAMEOVER;
                clock.reset();
            }
        }

        //KLEPANIE USTAWIEŃ
        playState.setGameSettings(gameFont, gameDifficulty, gameColor, gameHudColor, gameWordsSize);
        text_box.setColor(gameHudColor[0]);

        if (currentState == GameState::PLAY && pauseState == PauseState::RUNNING) {
            backGround1.move({-4.f, 0});
            backGround2.move({-4.f, 0});
        }
        if (backGround1.getPosition().x < -backGroundSize) {
            backGround1.setPosition(reset_Bg);
        }
        if (backGround2.getPosition().x < -backGroundSize) {
            backGround2.setPosition(reset_Bg);
        }

        window.clear();
        window.draw(backGround1);
        window.draw(backGround2);
        switch (currentState) {
            case GameState::MENU:
            case GameState::QUIT:
                menu.draw(window);
            break;
            case GameState::PLAY: {
                switch (pauseState) {
                    case PauseState::RUNNING:
                        playState.draw(window);
                        text_box.draw(window);
                    break;
                    case PauseState::GAMEOVER:
                        gameOverMenu.draw(window);
                    break;
                    default:
                        playState.draw(window);
                        text_box.draw(window);
                }
            }
            break;
            case GameState::SETTINGS:
                settingsMenu.draw(window);
            break;
        }

        if (pauseState == PauseState::PAUSED) {
            pause_menu.draw(window);
        }

        if (currentState == GameState::QUIT) {
            quit_menu.draw(window);
        }
        window.display();
    }
}

