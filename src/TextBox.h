
#ifndef TEXTBOX_H
#define TEXTBOX_H
#pragma once
#include <SFML/Graphics.hpp>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

#define MAX_LETTERS 15

//LINK DO FILMU
//https://www.youtube.com/watch?v=T31MoLJws4U

class TextBox {
public:

    TextBox(int size, sf::Color color, bool sel, sf::Font font);
    auto setColor(sf::Color color) -> void;
    auto setFont(sf::Font &font) -> void;
    auto setPosition(sf::Vector2f pos) -> void;
    auto setOriginCenter() -> void;
    auto setLimit(bool tf) -> void;
    auto setLimit(bool tf, int lim) -> void;
    auto setSelected(bool sel) -> void;
    auto getText() const -> std::string;
    auto getSelected() const -> bool;
    auto draw(sf::RenderWindow &window) -> void;
    auto typeOn(char c) -> void;

    auto getInput() const -> std::string {
        return input;
    }
    auto resetInput() -> void {
        input = "";
    }

private:
    sf::Text textBox;
    std::ostringstream text;
    bool isSelected = false;
    bool hasLimit = false;
    int limit = 0;
    std::string input;

    auto inputLogic(int charTyped) -> void;
    auto deleteLastChar() -> void;

};



#endif //TEXTBOX_H
