#include "Cestica.hpp"

Cestica::Cestica(sf::Vector2f pozicija, float radijus, int gx, int gy, int id)
{
    position = pozicija;
    position_last = pozicija;
    acceleration = {10.0f, 10.0f};
    radius = radijus;
    gridX = gx;
    gridY = gy;
    ID = id;
}

void Cestica::update(float deltaTime)
{
    sf::Vector2f displacement = position - position_last;
    position_last = position;
    position = position + displacement + acceleration * (deltaTime * deltaTime); //Verlet integration
    acceleration = {}; //Ubrzanje se vraca na nulu kako bi radilo kako treba

    gridX = position.x / 15;
    gridY = position.y / 15;
}

void Cestica::accelerate(sf::Vector2f a)
{
    acceleration += a;
}

void Cestica::setVelocity(sf::Vector2f v, float dt)
{
    position_last = position - (v*dt);
}

void Cestica::addVelocity(sf::Vector2f v, float dt)
{
    position_last -= v * dt;
}