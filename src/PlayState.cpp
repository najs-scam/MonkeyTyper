#include <iostream>
#include <format>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <ctime>
#include <set>
#include "PlayState.h"

PlayState::PlayState(float width, float height) :
    minutes(0),seconds(0),
    textTime(hudFont, "Time: 00:00"),
    score(0), textScore(hudFont, "Score: " + std::to_string(score)),
    totalWords(0), textTotalWords(hudFont, "Total Words: " + std::to_string(totalWords)),
    missedWords(0), textMissedWords(hudFont, "Missed Words: " + std::to_string(missedWords)),
    wordsPerMinute(0.f), textWordsPerMinute(hudFont, std::format("Words/Minutes: {:.2}", wordsPerMinute)),
    isWritingEnable(true),
    pointBuffer("rsrc/Audio/point.wav"),
    pointSound(pointBuffer),
    missedBuffer("rsrc/Audio/missed.wav"),
    missedSound(missedBuffer),
    wrongBuffer("rsrc/Audio/wrong.wav"),
    wrongSound(wrongBuffer),
    gameOverBuffer("rsrc/Audio/game-over-arcade-6435.wav"),
    gameOverSound(gameOverBuffer),
    textBoxBackground({300.f, 45.f})
{
    std::cout << "Konstruktor PlayState rozpoczety" << std::endl;
    //Settings
    gameFont = sf::Font("rsrc/Fonts/Arial.ttf");

    //HUD BAR
    hud_Bar.setSize(sf::Vector2f(width, 150.f));
    hud_Bar.setFillColor(sf::Color(30, 50, 70));
    hud_Bar.setPosition({
        width / 2 - hud_Bar.getSize().x / 2,
        height - hud_Bar.getSize().y
    });
    textBoxBackground.setOrigin(textBoxBackground.getGlobalBounds().getCenter());
    textBoxBackground.setPosition(sf::Vector2f(350, height-HUD_Y));
    textBoxBackground.setOutlineColor(sf::Color::White);
    textBoxBackground.setOutlineThickness(1.2f);
    textBoxBackground.setFillColor(sf::Color(0,0,0, 0));
    textTime.setOrigin(textTime.getGlobalBounds().getCenter());
    textTime.setPosition(sf::Vector2f(350, height - HUD_Y*2));
    textScore.setOrigin(textScore.getGlobalBounds().getCenter());
    textScore.setPosition(sf::Vector2f(width/2 , height - HUD_Y*2));
    textMissedWords.setOrigin(textMissedWords.getGlobalBounds().getCenter());
    textMissedWords.setPosition(sf::Vector2f(width/2, height - HUD_Y));
    textTotalWords.setOrigin(textTotalWords.getGlobalBounds().getCenter());
    textTotalWords.setPosition(sf::Vector2f(width-350, height - HUD_Y*2));
    textWordsPerMinute.setOrigin(textWordsPerMinute.getGlobalBounds().getCenter());
    textWordsPerMinute.setPosition(sf::Vector2f(width-350, height - HUD_Y));

    //WORDS POOLS
    auto loadWordsPool = [&](
        const std::string& filename,
        std::vector<WordObject>& words,
        sf::Color wordColor,
        int charSize = 30
        ) {
        std::ifstream file(filename);
        auto s = std::set<std::string>();
        if (!file) {
            std::cerr << "Error opening file " << filename << std::endl;
            return;
        }
        std::string word;
        while (std::getline(file, word)) {
            if (word.empty()) continue;
            s.insert(word);
        }
        for(auto it = s.begin(); it != s.end(); ++it) {
            WordObject wordObj(
                gameFont,  // Używamy istniejącej czcionki
                *it,      // Przekazujemy string zamiast sf::Text
                wordColor,
                charSize,
                false
            );
            wordObj.text.setOutlineColor(sf::Color::Black);
            wordObj.text.setOutlineThickness(1.f);
            words.emplace_back(wordObj);
        }
        std::cout << "Wczytano " << words.size() << " slow z pliku " << filename << std::endl;
    };
    loadWordsPool("rsrc/WordsPools/easy.txt", easyWords, sf::Color::Green);
    loadWordsPool("rsrc/WordsPools/normal.txt", normalWords, sf::Color::Green);
    loadWordsPool("rsrc/WordsPools/hard.txt", hardWords, sf::Color::Green);

    isWritingEnable = true;

    gameDifficulty = Difficulty::EASY;
    std::srand(time(nullptr));

    std::cout << "Liczba wczytanych slow (easy): " << easyWords.size() << std::endl;
    std::cout << "Konstruktor PlayState zakonczony" << std::endl;

    wrongSound.setVolume(60);
}

auto PlayState::draw(sf::RenderWindow& window) const -> void {
    window.draw(hud_Bar);
    window.draw(textTime);
    window.draw(textScore);
    window.draw(textMissedWords);
    window.draw(textTotalWords);
    window.draw(textWordsPerMinute);
    window.draw(textBoxBackground);
    drawWords(window);
}

auto PlayState::updateStats(float deltaTime) -> void {
    gameTime = deltaTime;
    timerUpdate(deltaTime);
    textScore.setString("Score: " + std::to_string(score));
    textTotalWords.setString("Total Words: " + std::to_string(totalWords));
    textMissedWords.setString("Missed Words: " + std::to_string(missedWords));
    textWordsPerMinute.setString(std::format("Words/Minutes: {:.4}", wordsPerMinute));
}

auto PlayState::timerUpdate(float deltaTime) -> void {
    auto totalSeconds = static_cast<int>(deltaTime);
    minutes = totalSeconds / 60;
    seconds = totalSeconds % 60;
    std::stringstream timeStream;
    timeStream << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    textTime.setString("Time: " + timeStream.str());
}

// WORDS
auto PlayState::GamePlay(float deltaTime) -> void {
    spawnTime += 0.005;
    generateWords();
    moveWords();
    positionColorChange();
    calculateWordsPerMinute();
    killWordOffScreen();
}

auto PlayState::generateWords() -> void {
    spawnCounter = static_cast<int>(spawnTime);
    int spawnDelay = 0;
    switch (gameDifficulty) {
        case Difficulty::EASY:
            spawnDelay = 2;
            break;
        case Difficulty::NORMAL:
            spawnDelay = 3;
            break;
        case Difficulty::HARD:
            spawnDelay = 4;
            break;
    }
    if (spawnCounter == spawnDelay && spawnIsEnabled) {
        for (int i = 0; i < rand() % 7 + 1; ++i)
            spawnWord();
        spawnTime = 0.f;
        spawnCounter = 0;
    }
}

auto PlayState::spawnWord() -> void {
    auto spawnWordByPool = [](std::vector<WordObject>& words) {
        if (words.empty()) return;
        int rI = rand() % words.size();
        int rY = (rand() % 18 + 1) * 35;
        auto check = true;
        auto newWordBounds = sf::FloatRect(
            {-words[rI].textWidth+100, static_cast<float>(rY)},
            {words[rI].textBounds.size.x, words[rI].textBounds.size.y}
        );
        if (!words[rI].isActive) {
            words[rI].text.setPosition(sf::Vector2f(-words[rI].textWidth, rY));
            for (auto& word : words) {
                if (word.isActive) {
                    auto existingWordBounds = sf::FloatRect(
                        { word.text.getPosition().x, word.text.getPosition().y},
                        {word.textBounds.size.x, word.textBounds.size.y}
                    );
                    if (newWordBounds.findIntersection(existingWordBounds)) {
                        check = false;
                        break;
                    }
                }
            }
            if (check) {
                words[rI].setPosition(0, static_cast<float>(rY));
                words[rI].isActive = true;
                words[rI].scoreWorth = 30;
            }
        }
    };

    switch (gameDifficulty) {
        case Difficulty::EASY:
            spawnWordByPool(easyWords);
            break;
        case Difficulty::NORMAL:
            spawnWordByPool(normalWords);
            break;
        case Difficulty::HARD:
            spawnWordByPool(hardWords);
            break;
    }
}

auto PlayState::eraseWord(WordObject& word) -> void {
    if (word.isActive) {
        word.isActive = false;
        word.setPosition(-1000, -1000);
    }
}

auto PlayState::killWordByInput(const std::string& input) -> void {
    auto killWords = [&](std::vector<WordObject>& words) {
        for (auto& word : words) {
            if (word.isActive && word.content == input) {
                pointSound.play();
                totalWords++;
                score += word.scoreWorth;
                eraseWord(word);
                break;
            }
        }
    };
    switch (gameDifficulty) {
        case Difficulty::EASY:
            killWords(easyWords);
            break;
        case Difficulty::NORMAL:
            killWords(normalWords);
            break;
        case Difficulty::HARD:
            killWords(hardWords);
            break;
    }

}

auto PlayState::killWordOffScreen() -> void {
    auto killWord = [&](std::vector<WordObject>& words) {
        for (auto& word : words) {
            if (word.isActive) {
                if (word.getPositon_X() >= (1490 + word.textWidth)) {
                    eraseWord(word);
                    missedWords++;
                    missedSound.play();
                }
            }
        }
    };
    switch (gameDifficulty) {
        case Difficulty::EASY:
            killWord(easyWords);
            break;
        case Difficulty::NORMAL:
            killWord(normalWords);
            break;
        case Difficulty::HARD:
            killWord(hardWords);
            break;
    }
}

auto PlayState::positionColorChange() -> void {
    auto posChangeColor = [&](std::vector<WordObject>& words) {
        for (auto& word : words) {
            if (word.isActive) {
                if (word.text.getPosition().x < 600)
                    word.text.setFillColor(gameColors[0]);
                else if (word.text.getPosition().x >= 600 && word.text.getPosition().x < 1100)
                    word.text.setFillColor(gameColors[1]);
                else if (word.text.getPosition().x >= 1100)
                    word.text.setFillColor(gameColors[2]);
            }
        }
    };
    switch (gameDifficulty) {
        case Difficulty::EASY:
            posChangeColor(easyWords);
            break;
        case Difficulty::NORMAL:
            posChangeColor(normalWords);
            break;
        case Difficulty::HARD:
            posChangeColor(hardWords);
            break;
    }
}

auto PlayState::moveWords() -> void {
    const auto speed = .32f;
    auto move = [&](std::vector<WordObject>& words) {
        for (auto& word : words) {
            if (word.isActive) {
                word.text.move({speed, 0});
                word.textBounds = word.text.getGlobalBounds();
                setScoreBaseOnPosition(word);
            }
        }
    };
    switch (gameDifficulty) {
        case Difficulty::EASY:
            move(easyWords);
            break;
        case Difficulty::NORMAL:
            move(normalWords);
            break;
        case Difficulty::HARD:
            move(hardWords);
            break;
    }

}

auto PlayState::checkWordCompletion(const std::string &input) -> bool {
    bool wordFound = false;
    auto checkCompletion = [&](std::vector<WordObject>& words) -> bool {
        return std::any_of(words.begin(), words.end(),
            [&](const auto& word) {
                if (word.isActive && word.content == input) {
                    wordFound = true;
                    return true;
                }
                return false;
            });
    };
    switch (gameDifficulty) {
        case Difficulty::EASY:
            checkCompletion(easyWords);
        break;
        case Difficulty::NORMAL:
            checkCompletion(normalWords);
        break;
        case Difficulty::HARD:
            checkCompletion(hardWords);
        break;
    }
    if (!wordFound && !input.empty()) {
        wrongSound.play();
    }
    return wordFound;
}

auto PlayState::setScoreBaseOnPosition(WordObject& word) -> void {
    auto intPos = static_cast<int>(word.getPositon_X());
    word.scoreWorth = (1500 - intPos) / 50 + 1;

}

auto PlayState::drawWords(sf::RenderWindow& window) const -> void {
    auto drawing = [&](const std::vector<WordObject>& words) {
        for (auto& word : words)
            if (word.isActive)
                window.draw(word.text);
    };
    switch (gameDifficulty) {
        case Difficulty::EASY:
            drawing(easyWords);
            break;
        case Difficulty::NORMAL:
            drawing(normalWords);
            break;
        case Difficulty::HARD:
            drawing(hardWords);
            break;
    }
}

auto PlayState::gameOver() -> bool {
    if (missedWords >= 10) {
        missedSound.stop();
        gameOverSound.play();
        return true;
    }
    return false;
}

auto PlayState::resetGame() -> void {
    auto eraseAll = [&](std::vector<WordObject>& words) {
        for (auto& word : words)
            if (word.isActive)
                eraseWord(word);
    };
    switch (gameDifficulty) {
        case Difficulty::EASY:
            eraseAll(easyWords);
            break;
        case Difficulty::NORMAL:
            eraseAll(normalWords);
            break;
        case Difficulty::HARD:
            eraseAll(hardWords);
            break;
    }
    score = 0;
    totalWords = 0;
    missedWords = 0;
    wordsPerMinute = 0.f;
}

auto PlayState::calculateWordsPerMinute() -> void {
    if (gameTime > 0.f) {
        wordsPerMinute = (totalWords / gameTime) * 60.f;
    }
}

auto PlayState::getPlayerStatistics() -> StatsObject {
    auto stats = StatsObject(
        minutes, seconds, score,totalWords, wordsPerMinute, gameDifficulty);
    return stats;
}

auto PlayState::setGameFont(sf::Font& font) -> void {
    gameFont = font;
    for (auto& word : easyWords)
        word.setFont(gameFont);
}

auto PlayState::setGameSettings(sf::Font &font, Difficulty &difficulty, std::vector<sf::Color> &fontColors,
    std::vector<sf::Color> &hudColors, int wordSize) -> void {
    gameFont = font;
    gameDifficulty = difficulty;
    gameColors = fontColors;
    gameHudColors = hudColors;
    gameSizeWords = wordSize;

    auto set_font = [&](std::vector<WordObject>& words) {
        for (auto& word : words) {
            word.setFont(gameFont);
            word.setWordSize(wordSize);
        }
    };
    switch (gameDifficulty) {
        case Difficulty::EASY:
            set_font(easyWords);
            break;
        case Difficulty::NORMAL:
            set_font(normalWords);
            break;
        case Difficulty::HARD:
            set_font(hardWords);
            break;
    }
    //HUD
    hud_Bar.setFillColor(hudColors[1]);
    textBoxBackground.setOutlineColor(hudColors[0]);
    textTime.setFillColor(hudColors[0]);
    textScore.setFillColor(hudColors[0]);
    textTotalWords.setFillColor(hudColors[0]);
    textMissedWords.setFillColor(hudColors[0]);
    textWordsPerMinute.setFillColor(hudColors[0]);
}
