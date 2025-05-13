#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Button.hpp"
#include "Cestica.hpp"
#include "Solver.hpp"

class CesticeSimulacija : public State
{
    public:
        int handleInput(sf::RenderWindow& window, const sf::Event& event) override;
        void update(sf::Time deltaTime) override;
        void render(sf::RenderWindow& window) override;

        CesticeSimulacija(sf::RenderWindow* window, sf::Font font, Solver &solver);
        virtual ~CesticeSimulacija();
    private:
        sf::Font font;
        Cestica objekat;
        Solver& solver;
};