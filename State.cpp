#include "State.hpp"
#include <SFML/Graphics.hpp>

State::State(sf::RenderWindow* window, sf::Font font)
{
    this->window = window;
    this->font = font;
}
