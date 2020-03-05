#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Map.hpp"
#include "barrels.hpp"

class Player
{
  public:
    Player(sf::Texture& image);
    ~Player();
    void update(float time);
    void render(sf::RenderWindow* rw);
    void handleInput();
    void collision(int dir);
    
    void setXpos(float x) { dx_ = x;}
    float getXpos() {return dx_;}
    
    void setYpos(float y) { dy_ = y;}
    float getYpos() {return dy_;}

    bool hasWeapon() {return weapon_; }
    
    void setSpaceHold(bool hold) {spaceHold_ = hold;}
    bool isSpaceHold() {return spaceHold_;}

    void setPlayerRect(sf::FloatRect rect) {rect_ = rect;}
    sf::FloatRect getPlayerRect() {return rect_;}
    
    void setOnGround(bool ground) {onGround_ = ground;}
    bool getOnGround() {return onGround_;}
    
    void setButton(bool press) {buttonPressed_ = press;}
    bool getButton() {return buttonPressed_;}

    void setHealth(int health) { health_ = health; }
    int getHealth() {return health_;}
    
    bool hitPrincess() {return hitPrincess_;}
    bool showName() {return showName_;}
  private:
    float dx_;
    float dy_;
    sf::FloatRect rect_;
    bool onGround_;
    sf::Sprite sprite_;
    bool stairs_;
    bool direction_;
    bool weapon_;
    bool spaceHold_;
    int health_;
    sf::Sound* jump_;
    sf::SoundBuffer* jumpBuffer_;
    bool showName_;
    bool buttonPressed_;
    bool hitPrincess_;
    float currentFrame_;
};
#endif //PLAYER_HPP
