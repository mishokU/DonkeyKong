#include "Monkey.hpp"
#include <iostream>

Monkey::Monkey(sf::Texture& image,int row,int column)
{
  sprite_.setTexture(image);
  sprite_.setPosition(column*PixelPerCell - 11,row*PixelPerCell);
  sprite_.setScale(2,2);
  currentFrame_ = 0;
  throw_ = false;
}

void Monkey::update(float time)
{  
  currentFrame_ += 0.0012*time;

  if((currentFrame_ >= 2 && currentFrame_ <= 2.03))
  {
    throw_ = true;
  }
  
  if (currentFrame_ > 3) currentFrame_ -= 3;
  
  sprite_.setTextureRect(sf::IntRect(44*int(currentFrame_)+1,154,44,32));
}

void Monkey::render(sf::RenderWindow* rw)
{
  rw->draw(sprite_);
}
