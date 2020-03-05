#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "SFML/Graphics.hpp"
#include <cstring>

class MainMenu
{
  public:
    MainMenu();
    ~MainMenu();

    void setCommand(std::string command);
    std::string getCommand();    
    
    bool openExitMenu();
    
    void setName();
    void setPoints(sf::Text text);
    void handleInput();
    void render(sf::RenderWindow* rw);

  private:
    std::string command_;
    std::string tmpCom_;
    sf::Sprite* donkeyName_;
    sf::Texture* texture;
    sf::Font* font_;
    sf::Text* startText_;
    sf::Text* points_;
    sf::Text* exitText_;
    sf::RectangleShape startShape_;
    sf::RectangleShape exitShape_;
    sf::RectangleShape movingShape_;
};



#endif //MAINMENU_HPP