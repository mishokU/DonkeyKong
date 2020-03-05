#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "SFML/Graphics.hpp"

class Button
{
  public:
    Button(sf::Texture& image);
    
    void render(sf::RenderWindow* rw);

    sf::FloatRect getButtonRect() {return rect_;}
    
    void setButtonPressed(bool press);
    bool isButtonPressed() {return isPressed_; }
    
  private:
    sf::Sprite sprite_;  
    sf::FloatRect rect_;
    bool isPressed_;
};

#endif //BUTTON_HPP