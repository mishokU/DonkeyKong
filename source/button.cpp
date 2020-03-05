#include "button.hpp"

Button::Button(sf::Texture& image)
{
  rect_ = sf::FloatRect(1*16,30*16,6,11);
  sprite_.setTexture(image);
  sprite_.setPosition(1*16,30*16);
  sprite_.setScale(2,2);
  sprite_.setTextureRect(sf::IntRect(326,277,6,11));
  isPressed_ = false;
}

void Button::setButtonPressed(bool press)
{
  if(press)
  {
    sprite_.setTextureRect(sf::IntRect(334,277,6,11));
    isPressed_ = true;
  }
  if(!press)
  {
    sprite_.setTextureRect(sf::IntRect(326,277,6,11));  
    isPressed_ = false;
  }
}

void Button::render(sf::RenderWindow* rw)
{
  rw->draw(sprite_);
}