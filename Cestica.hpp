#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"

class Cestica
{
    public:
        Cestica() = default;
        Cestica(sf::Vector2f pozicija, float radius, int gx, int gy, int id);

        void update(float deltaTime);
        void accelerate(sf::Vector2f a);
        void setVelocity(sf::Vector2f v, float dt);
        void addVelocity(sf::Vector2f v, float dt);

        sf::Vector2f getVelocity()
        {
            return position - position_last;
        }

        sf::Vector2f getPosition()
        {
            return position;
        }

        float getRadius()
        {
            return radius;
        }

        void setPosition(sf::Vector2f position)
        {
            this->position = position;
        }

        sf::Color getColor()
        {
            return this->color;
        }

        void setColor(sf::Color boja)
        {
            this->color = boja;
        }

        int getID()
        {
            return ID;
        }

        int getGridX()
        {
            return gridX;
        }

        void setGridX(int gridx)
        {
            this->gridX = gridx;
        }

        int getGridY()
        {
            return gridY;
        }

        void setGridY(int gridy)
        {
            this->gridY = gridy;
        }
        
    private:
        sf::Vector2f position;
        sf::Vector2f position_last;
        sf::Vector2f acceleration;
        float radius = 10.0f;
        sf::Color color = sf::Color::Magenta;
        int gridX = 0, gridY = 0, ID = 0;
};