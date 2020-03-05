#include "Game.hpp"

Game::Game()
{
  renderWindow_ = nullptr;
  healthText_ = nullptr;
  pointsText_ = nullptr;
  isRunning_ = true;
  points_ = 0;
  time_ = 0;
}

Game::~Game()
{
  if(renderWindow_)
   delete renderWindow_;
 
  if(healthText_)
    delete healthText_;
    
  if(font_)
    delete font_;
  
  if(pointsText_)
    delete pointsText_;

  if(texture_)
   delete texture_;
}

void Game::setUpSystem(const char* title,const size_t width,const size_t height)
{
  renderWindow_ = new sf::RenderWindow(sf::VideoMode(width,height),title);
   
  texture_     = new sf::Texture(); 
  texture_->loadFromFile("tileSpriteDonkeyKong.png");
  tile_.setTexture(*texture_);
  
  player_      = std::make_unique<Player>(*texture_);
  monkey_      = std::make_unique<Monkey>(*texture_,4,6);
  button_      = std::make_unique<Button>(*texture_);
  mainMenu_    = std::make_unique<MainMenu>();
  font_        = new sf::Font();
  healthText_  = new sf::Text();
  pointsText_  = new sf::Text();
  soundBuffer_ = std::make_unique<sf::SoundBuffer>();
  smashBarrel_ = std::make_unique<sf::Sound>();

  barrels_.push_back(std::make_unique<Barrel>(*texture_));
  
  font_->loadFromFile("arial.ttf");
  
  soundBuffer_->loadFromFile("smashBarrel.wav");
  smashBarrel_->setBuffer(*soundBuffer_);

  healthText_->setFont(*font_);
  pointsText_->setFont(*font_);
  
  healthText_->setPosition(690,29);
  healthText_->setCharacterSize(20);
  healthText_->setStyle(sf::Text::Regular);
  healthText_->setFillColor(sf::Color::White);
  healthText_->setString("12");
  
  pointsText_->setPosition(830,29);
  pointsText_->setCharacterSize(20);
  pointsText_->setStyle(sf::Text::Bold);
  pointsText_->setFillColor(sf::Color::White);
  pointsText_->setString("0");
  
  renderWindow_->setFramerateLimit(60);
  renderWindow_->setVerticalSyncEnabled(true);
}

void Game::drawMap()
{
  for (int i=0; i< Height; i++)
  {
    for (int j=0; j< Width; j++)
    { 
      if (tileMap[i][j] == '#') tile_.setTextureRect(sf::IntRect(15,556,8,8));
      if (tileMap[i][j] == 'S') tile_.setTextureRect(sf::IntRect(78,379,10,9));
      if (tileMap[i][j] == 'P') tile_.setTextureRect(sf::IntRect(99,20,41,26));
      if (tileMap[i][j] == 'F') tile_.setTextureRect(sf::IntRect(238,281,18,32));
      if (tileMap[i][j] == 'B') tile_.setTextureRect(sf::IntRect(268,279,22,34));
      if (tileMap[i][j] == 'T') tile_.setTextureRect(sf::IntRect(245,76,13,10));
      if (tileMap[i][j] == 'C') tile_.setTextureRect(sf::IntRect(303,220,49,21));
      if (tileMap[i][j] == 'J') tile_.setTextureRect(sf::IntRect(303,244,49,23));
      if (tileMap[i][j] == 'W') tile_.setTextureRect(sf::IntRect(242,152,11,12));
      if (tileMap[i][j] == 'H') tile_.setTextureRect(sf::IntRect(78,379,10,9));
      if (tileMap[i][j] == 'E') tile_.setTextureRect(sf::IntRect(25,2,8,8));
      if (tileMap[i][j] == '$') tile_.setTextureRect(sf::IntRect(78,379,10,9));

      if(player_->showName())
      {
        if(tileMap[i][j] == 'E') tile_.setTextureRect(sf::IntRect(0,1,21,8));
      }

      if(player_->hasWeapon())
      {
        if (tileMap[i][j] == 'W') tile_.setTextureRect(sf::IntRect(25,2,8,8)); 
      }
      
      if(!button_->isButtonPressed())
      {
        if (tileMap[i][j] == 'P') tile_.setTextureRect(sf::IntRect(12,22,16,22));  
        if (tileMap[i][j] == 'H') tile_.setTextureRect(sf::IntRect(15,556,8,8));
      }
      
      if (tileMap[i][j] == 'K' || tileMap[i][j] == ' ' || tileMap[i][j] == 'X' || tileMap[i][j] == '@') continue;
      
      tile_.setScale(2,2);
      tile_.setPosition(j* PixelPerCell,i* PixelPerCell) ; 
      renderWindow_->draw(tile_);
    }
  }
}

bool Game::loop()
{
  if(!renderWindow_->isOpen() || mainMenu_->getCommand() == "exit")
  {
    return false;
  }
  
  float time = clock_.getElapsedTime().asMicroseconds();
  clock_.restart();

  time = time / 700;
  if(time > 20) time = 20;
  
  handleEvent();
  
  if(mainMenu_->getCommand() == "start")
  {
    update(time);
  }
  render();
  
  return isRunning_;
}

void Game::handleEvent()
{
  sf::Event event;
  while(renderWindow_->pollEvent(event))
  {
    if(event.type == sf::Event::Closed)
      renderWindow_->close();
  }
}

void Game::update(float dt)
{
  player_->update(dt);
  monkey_->update(dt);

  if(monkey_->getThrow())
  {
    barrels_.push_back(std::make_unique<Barrel>(*texture_));
    monkey_->setThrow(false);
  }

  if(player_->getHealth() < 0)
  {
    mainMenu_->setCommand("defeat");
    mainMenu_->setPoints(*pointsText_);
  }
  
  if(player_->hitPrincess())
  {
    mainMenu_->setCommand("win");
    mainMenu_->setPoints(*pointsText_);
  }
  
  if(player_->getPlayerRect().intersects(button_->getButtonRect()))
  {
    button_->setButtonPressed(true);
    player_->setButton(true);
  }

  if(button_->isButtonPressed())
  {
    for(auto& b : barrels_)
    {
      if(b->getTileYpos() != 33)
      {
        b->setTileYpos(33);
        b->setSpeed(0.0105);
      }
    }
  }
  
  for(auto it = barrels_.begin(); it != barrels_.end(); )
  {
    (*it)->update(dt);
    
    if(player_->hasWeapon())
    {
      if(player_->isSpaceHold())
      {
        if(player_->getPlayerRect().intersects((*it)->getBarrelRect()))
        {
          it = barrels_.erase(it);
          smashBarrel_->play();
          points_ += 100;
          out_ << points_;
          pointsText_->setString(out_.str());
          out_.str("");
          continue;
        }
      }
    }

    if(player_->getPlayerRect().intersects((*it)->getBarrelRect()))
    { 
      player_->setHealth(player_->getHealth() - 1);
      out_ << player_->getHealth();
      healthText_->setString(out_.str());
      out_.str("");
    }
    //Доделать
    if(((*it)->getBarrelRect().top - player_->getPlayerRect().top > EPSILON) && 
      ((*it)->getBarrelRect().left - player_->getPlayerRect().left == -2))
    {
      points_ += 100;
      out_ << points_;
      pointsText_->setString(out_.str());
      out_.str("");
    }

    if((*it)->getStopFlag())
    {
      it = barrels_.erase(it);
      button_->setButtonPressed(false);
      player_->setButton(false);
    }
    else
    {
      ++it;
    }
  }
}

void Game::render()
{
  renderWindow_->clear(sf::Color::Black);
  
  if(mainMenu_->getCommand() == "start")
  {
    drawMap();
    
    player_->render(renderWindow_);
    monkey_->render(renderWindow_);
    button_->render(renderWindow_);
    
    renderWindow_->draw(*healthText_);
    renderWindow_->draw(*pointsText_);

    for(auto& b : barrels_)
    {
      b->render(renderWindow_);
    }
  }
  else
  {
    mainMenu_->render(renderWindow_);
  }

  renderWindow_->display();
}