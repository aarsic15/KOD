#include "Button.hpp"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Font* font, std::string text, 
    sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
      : font(font),
        text(*font, text, 12)
{
    this->buttonState = BTN_IDLE;

    this->shape.setPosition(position);
    this->shape.setSize(size);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(12);
    sf::FloatRect textBounds = this->text.getLocalBounds();
    this->text.setOrigin
    (
        {textBounds.size.x / 2.f,
         textBounds.size.y / 2.f}
    );
    this->text.setPosition
    (
        {this->shape.getPosition().x + (this->shape.getGlobalBounds().size.x / 2.f) - this->text.getGlobalBounds().size.x / 2.f,
         this->shape.getPosition().y + (this->shape.getGlobalBounds().size.y / 2.f) - this->text.getGlobalBounds().size.y / 2.f}
    );

    this->idleColor = idleColor;
    this->clickColor = clickColor;
    this->hoverColor = hoverColor;

    this->shape.setFillColor(idleColor);

}

Button::~Button()
{

}

//Cisto update kako bih proveravao da li se menja stanje izmedju idle, hover i active
void Button::update(const sf::Vector2f mousePos)
{
    this->buttonState = BTN_IDLE;

    //za prebac na hover
    if(this->shape.getGlobalBounds().contains(mousePos))
    {
        this->buttonState = BTN_HOVER;

        //za prebac na klik
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            this->buttonState = BTN_PRESSED;
        }
    }

    switch(this->buttonState)
    {
        case BTN_IDLE:
            this->shape.setFillColor(this->idleColor);
            break;
        case BTN_HOVER:
            this->shape.setFillColor(this->hoverColor);
            break;
        case BTN_PRESSED:
            this->shape.setFillColor(this->clickColor);
            break;
        
        default:
            this->shape.setFillColor(sf::Color::Black);
    }
}

const bool Button::isPressed() const
{
    if(this->buttonState == BTN_PRESSED)
        return true;
    return false;
}

void Button::changeCharSize(const int &size)
{
    this->text.setCharacterSize(size);
}

//rendering funkcija za dugmic
void Button::render(sf::RenderWindow* target)
{
    target->draw(this->shape);
    target->draw(this->text);
}