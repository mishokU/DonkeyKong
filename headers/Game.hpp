#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <memory>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Player.hpp"
#include "barrels.hpp"
#include "Map.hpp"
#include "Monkey.hpp"
#include "button.hpp"
#include "MainMenu.hpp"

constexpr float EPSILON = 10;

class Game
{
  public:
    Game();
    ~Game();
    
    void setUpSystem(const char* title,const size_t width,const size_t height);
    
    void drawMap();
    void update(float dt);
    void render();
    void handleEvent();
    bool loop();
    
    
  private:
    sf::RenderWindow* renderWindow_;
    sf::Clock clock_;
    sf::Texture* texture_;
    sf::Text* healthText_;
    sf::Text* pointsText_;
    sf::Font* font_;
    sf::Sprite tile_;
    
    std::ostringstream out_;
    std::vector<std::unique_ptr<Barrel>> barrels_;
    std::unique_ptr<Player> player_;
    std::unique_ptr<Monkey> monkey_;
    std::unique_ptr<Button> button_;
    std::unique_ptr<MainMenu> mainMenu_;
    std::unique_ptr<sf::SoundBuffer> soundBuffer_;
    std::unique_ptr<sf::Sound> smashBarrel_;

    bool isRunning_;
    int points_;
    float time_;
};

#endif //GAME_HPP