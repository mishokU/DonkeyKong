#ifndef MONKEY_HPP
#define MONKEY_HPP

#include "SFML/Graphics.hpp"
#include "Map.hpp"

class Monkey
{
  public:
    Monkey(sf::Texture& image,int row,int column);
    
    void update(float time);
    void render(sf::RenderWindow* rw);

    void setThrow(bool throwf) {throw_ = throwf;}
    bool getThrow() {return throw_;}
    
  private:
    bool throw_;
    sf::Sprite sprite_;  
    float currentFrame_;
};
#endif //MONKEY_HPP
