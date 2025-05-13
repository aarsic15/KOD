#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};

class Button
{
    private: 
        short unsigned buttonState;

        sf::RectangleShape shape;
        sf::Font* font;
        sf::Text text;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color clickColor;

    public:
        Button(sf::Vector2f position, sf::Vector2f size, sf::Font* font, std::string text, 
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

        ~Button();

        const bool isPressed() const;

        void changeCharSize(const int &size);
        void update(const sf::Vector2f mousePos);
        void render(sf::RenderWindow* window);

};

#endif