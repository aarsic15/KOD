#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class State
{
    public:
        State(sf::RenderWindow* window, sf::Font font);
        virtual int handleInput(sf::RenderWindow& window, const sf::Event& event) = 0;
        virtual void update(sf::Time deltaTime) = 0;
        virtual void render(sf::RenderWindow& window) = 0;
        virtual void updateMousePosition()
        {
            this->mousePosScreen = sf::Mouse::getPosition();
            this->mousePosWindow = sf::Mouse::getPosition(*this->window);
            this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
        };
        virtual ~State() {};

    protected:
        sf::Font font;
        sf::RenderWindow* window;

        sf::Vector2i mousePosScreen;
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;
};