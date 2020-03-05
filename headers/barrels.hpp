#ifndef BARRELS_HPP
#define BARRELS_HPP

#include "SFML/Graphics.hpp"
#include "Map.hpp"

class Barrel
{
  public:
  
    Barrel(sf::Texture& image);
    
    void update(float time);
    void render(sf::RenderWindow* rw);
    void collision(int dir);

    void setSpeed(float speed) { speed_ = speed;}
    
    void setTileYpos(float y) { tileYpos_ = y;}
    float getTileYpos() {return tileYpos_;}

    void setXpos(float x) { dx_ = x;}
    float getXpos() {return dx_;}
    
    bool getStopFlag() {return stop_;}
    
    void setBarrelRect(sf::FloatRect rect) {rect_ = rect;}
    sf::FloatRect getBarrelRect() {return rect_;}
    
  private:
    float dx_;
    float dy_;
    float tileYpos_;
    float speed_;
    float currentFrame_;
    sf::FloatRect rect_;
    sf::Sprite tile;
    sf::Sprite sprite_;
    bool onGround_;
    bool stop_;
    bool direction_;
};
#endif //BARRELS_HPP