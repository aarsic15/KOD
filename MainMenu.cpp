#include "MainMenu.hpp"
#include "State.hpp"

MainMenu::MainMenu(sf::RenderWindow* window, sf::Font font)
    : State(window, font)
{
    this->font = font;

    this->cestice = new Button({250, 475}, {250, 150}, &this->font, "Simulacija cestica",
                                sf::Color(70, 70, 70, 200),
                                sf::Color(150, 150, 150, 200),
                                sf::Color(20, 20, 20, 200));
    
    this->cestice->changeCharSize(25);
}

MainMenu::~MainMenu()
{
    delete this->cestice;
}

int MainMenu::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
    if(cestice->isPressed())
        return 1;
    return 0;
}

void MainMenu::update(sf::Time deltaTime)
{
    this->updateMousePosition();
    this->cestice->update(this->mousePosView);
}

void MainMenu::render(sf::RenderWindow& window)
{
    cestice->render(&window);
}