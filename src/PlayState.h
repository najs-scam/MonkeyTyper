#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#pragma once

#define HUD_FONT_SIZE 30
#define HUD_Y 50.f

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <vector>
#include <string>
#include "Difficulty.h"
#include "StatsObject.h"

class PlayState {

    struct WordObject {
        sf::Text text;
        std::string content;
        bool isActive;
        sf::FloatRect textBounds;
        float textWidth;
        int scoreWorth;

        WordObject(const sf::Font& font, const std::string& word,
                   sf::Color color, int charSize, bool active) :
            text(font, word, charSize),
            content(word),
            isActive(active),
            textBounds(text.getGlobalBounds())
        {
            text.setFillColor(color);
            text.setOrigin(textBounds.size);
            textWidth = textBounds.size.x;
        }

        void setPosition(float x, float y) {
            text.setPosition({x, y});
        }
        auto getPositon_X() -> float {
            return text.getPosition().x;
        }
        void setScore(int score) {
            scoreWorth = score;
        }
        auto setFont(const sf::Font& font) -> void {
            text.setFont(font);
        }
        auto setWordSize(int size) -> void {
            text.setCharacterSize(size);
        }
    };

    std::vector<WordObject> easyWords;
    std::vector<WordObject> normalWords;
    std::vector<WordObject> hardWords;

    float spawnTime = 0.f;
    int spawnCounter = 0;
    bool spawnIsEnabled = true;

    //DOLNY PASEK
    sf::RectangleShape hud_Bar;
    sf::Font hudFont = sf::Font("rsrc/Fonts/Arial.ttf");
    sf::RectangleShape textBoxBackground;
    float elapsedTime;
    int minutes;
    int seconds;
    sf::Text textTime;
    int score;
    sf::Text textScore;
    int totalWords;
    sf::Text textTotalWords;
    int missedWords;
    sf::Text textMissedWords;
    float wordsPerMinute;
    sf::Text textWordsPerMinute;

    //SETTINGS
    sf::Font gameFont;
    Difficulty gameDifficulty;
    std::vector<sf::Color> gameColors;
    std::vector<sf::Color> gameHudColors;
    int gameSizeWords;

    float gameTime;

    sf::SoundBuffer pointBuffer;
    sf::Sound pointSound;
    sf::SoundBuffer missedBuffer;
    sf::Sound missedSound;
    sf::SoundBuffer wrongBuffer;
    sf::Sound wrongSound;
    sf::SoundBuffer gameOverBuffer;
    sf::Sound gameOverSound;

public:

    bool isWritingEnable;
    PlayState(float width, float height);
    auto draw(sf::RenderWindow& window) const -> void;
    auto updateStats(float deltaTime) -> void;
    auto timerUpdate(float deltaTime) -> void;
    auto getTextBoxBack() const -> sf::RectangleShape {
        return textBoxBackground;
    }

    auto GamePlay(float deltaTime) -> void;
    auto spawnWord() -> void;
    auto generateWords() -> void;

    auto eraseWord(WordObject& word) -> void;
    auto killWordByInput(const std::string& input) -> void;
    auto killWordOffScreen() -> void;
    auto positionColorChange() -> void;
    auto moveWords() -> void;
    auto checkWordCompletion(const std::string &) -> bool;

    auto setScoreBaseOnPosition(WordObject& word) -> void;

    auto drawWords(sf::RenderWindow& window) const -> void;

    auto gameOver() -> bool;
    auto resetGame() -> void;
    auto calculateWordsPerMinute() -> void;

    auto getPlayerStatistics() -> StatsObject;
    //SET SETTINGS
    auto setGameFont(sf::Font& font) -> void;
    auto setGameSettings(
        sf::Font& font,
        Difficulty& difficulty,
        std::vector<sf::Color>& fontColors,
        std::vector<sf::Color>& hudColors,
        int wordSize) -> void;

};



#endif //PLAYSTATE_H
