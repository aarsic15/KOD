#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Button.hpp"

class MainMenu : public State
{
    public:
        int handleInput(sf::RenderWindow& window, const sf::Event& event) override;
        void update(sf::Time deltaTime) override;
        void render(sf::RenderWindow& window) override;

        MainMenu(sf::RenderWindow* window, sf::Font font);
        virtual ~MainMenu();

    private:
        sf::Font font;

        Button* cestice;
};