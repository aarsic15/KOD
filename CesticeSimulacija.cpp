#include "CesticeSimulacija.hpp"

CesticeSimulacija::CesticeSimulacija(sf::RenderWindow* window, sf::Font font, Solver &solver)
    : State(window, font), solver(solver)
{
    this->font = font;
}

CesticeSimulacija::~CesticeSimulacija() {}

int CesticeSimulacija::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
    /*    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) 
    {
        if(mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
            float ratio = 1920.0f / window.getSize().x; // Correct for scaled window
            sf::Vector2f pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) * ratio;
            solver.mousePull(pos);
        }
    }

    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if(mouseButtonPressed->button == sf::Mouse::Button::Right)
        {
            float ratio = 1920.0f / window.getSize().x; // Correct for scaled window
            sf::Vector2f pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) * ratio;
            solver.mousePush(pos);
        }
        
    }*/
    return 0;
}

void CesticeSimulacija::update(sf::Time deltaTime)
{
    solver.update();
}

void CesticeSimulacija::render(sf::RenderWindow& window)
{
    /*
    //crni krugic koji glumi pozadinu
    const sf::Vector3f boundary = solver.getBoundary();
    sf::CircleShape boundary_background{boundary.z};
    boundary_background.setOrigin({boundary.z, boundary.z});
    boundary_background.setFillColor(sf::Color::Black);
    boundary_background.setPosition({boundary.x, boundary.y});
    boundary_background.setPointCount(128);
    window.draw(boundary_background);*/

    //Objekti koji se crtaju na ekran (kuglice)
    sf::CircleShape circle{1.0f};
    circle.setPointCount(32);
    circle.setOrigin({1.0f, 1.0f});
    auto &objects = solver.getObjects();
    for(auto &obj : objects)
    {
        circle.setPosition(obj.getPosition());
        circle.setScale({obj.getRadius(), obj.getRadius()});
        circle.setFillColor(obj.getColor());
        window.draw(circle);
    }
}