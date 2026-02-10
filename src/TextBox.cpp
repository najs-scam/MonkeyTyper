#include "TextBox.h"
#include <iostream>
#include <sstream>

//LINK DO FILMU
//https://www.youtube.com/watch?v=T31MoLJws4U

TextBox::TextBox(int size, sf::Color color, bool sel, sf::Font font): textBox(font) {
    textBox.setFont(font);
    textBox.setCharacterSize(size);
    textBox.setFillColor(color);
    isSelected = sel;
    if (sel) {
        textBox.setString("_");
    } else {
        textBox.setString("");
    }
}

auto TextBox::setColor(sf::Color color) -> void {
        textBox.setFillColor(color);
}

auto TextBox::setFont(sf::Font &font) -> void {
    textBox.setFont(font);
}

auto TextBox::setPosition(sf::Vector2f pos) -> void {
    textBox.setPosition(pos);
}

auto TextBox::setOriginCenter() -> void {
    textBox.setOrigin(textBox.getGlobalBounds().getCenter());
}

auto TextBox::setLimit(bool tf) -> void {
    hasLimit = tf;
    limit = MAX_LETTERS;
}

auto TextBox::setLimit(bool tf, int lim) -> void {
    hasLimit = tf;
    limit = lim;
}

auto TextBox::setSelected(bool sel) -> void {
    isSelected = sel;
    if (!sel) {
        std::string tmp = text.str();
        std::string newT = tmp.substr(0, tmp.length());
        textBox.setString(newT);
    } else {
        textBox.setString(text.str() + "_");
    }
}

auto TextBox::getText() const -> std::string {
    return text.str();
}

auto TextBox::getSelected() const -> bool {
    return isSelected;
}

auto TextBox::draw(sf::RenderWindow &window) -> void {
    window.draw(textBox);
}

auto TextBox::typeOn(char c) -> void {
    if (isSelected) {
        int charType = c;
        if (charType < 128) {
            if (hasLimit) {
                if (text.str().length() <= limit) {
                    inputLogic(charType);
                }
            } else {
                inputLogic(charType);
            }
        }
    }
}

auto TextBox::inputLogic(int charTyped) -> void {
    // Sprawdzamy czy osiągnięto limit znaków
    bool atLimit = (text.str().length() >= limit);

    if (charTyped == DELETE_KEY) {
        // Zawsze pozwalamy na backspace, niezależnie od limitu
        if (text.str().length() > 0) {
            deleteLastChar();
        }
    }
    else if (!atLimit && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
        // Pozwalamy na nowe znaki tylko jeśli nie osiągnięto limitu
        text << static_cast<char>(charTyped);
    } else if (charTyped == ENTER_KEY) {
        if (text.str().length() > 1) {
            input = text.str();
            std::cout << input << std::endl;
            text.str("");
        }
    }

    // Aktualizacja wyświetlanego tekstu
    if (isSelected) {
        if (text.str().length() < limit) {
            textBox.setString(text.str() + "_");
        } else {
            textBox.setString(text.str());
        }
    } else {
        textBox.setString(text.str());
    }
}

auto TextBox::deleteLastChar() -> void {
    std::string tmp = text.str();
    std::string newT = tmp.substr(0, tmp.length() - 1);
    text.str("");
    text << newT;

    if (isSelected) {
        textBox.setString(text.str() + "_");
    } else {
        textBox.setString(text.str());
    }
}
