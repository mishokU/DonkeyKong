#include "MainMenu.hpp"

MainMenu::MainMenu()
{
  startShape_ = sf::RectangleShape();
  startShape_.setPosition(405,255);
  startShape_.setSize(sf::Vector2f(190,30));
  startShape_.setFillColor(sf::Color::Green);
  
  exitShape_ = sf::RectangleShape();
  exitShape_.setPosition(405,355);
  exitShape_.setSize(sf::Vector2f(190,30));
  exitShape_.setFillColor(sf::Color::Red);

  movingShape_ = sf::RectangleShape();
  movingShape_.setPosition(400,350);
  movingShape_.setSize(sf::Vector2f(200,40));
  movingShape_.setOutlineThickness(-5);
  movingShape_.setOutlineColor(sf::Color::White);

  font_ = new sf::Font();
  font_->loadFromFile("arial.ttf"); 

  startText_ = new sf::Text();
  startText_->setFont(*font_);
  startText_->setPosition(465,255);
  startText_->setCharacterSize(20);
  startText_->setFillColor(sf::Color::White);
  startText_->setStyle(sf::Text::Bold);
  startText_->setString("START");

  points_ = new sf::Text();
  points_->setFont(*font_);
  points_->setPosition(410,300);
  points_->setCharacterSize(30);
  points_->setFillColor(sf::Color::Black);
  points_->setString("You have: ");
   
  exitText_ = new sf::Text();
  exitText_->setFont(*font_);
  exitText_->setPosition(470,355);
  exitText_->setCharacterSize(20);
  exitText_->setFillColor(sf::Color::White);
  exitText_->setStyle(sf::Text::Bold);
  exitText_->setString("EXIT");

  texture = new sf::Texture();
  texture->loadFromFile("DonkeyKongLike.png");

  donkeyName_ = new sf::Sprite();
  donkeyName_->setScale(0.5,0.5);
  donkeyName_->setTexture(*texture);
  donkeyName_->setPosition(50,50);

  command_ = "";
  tmpCom_  = "";
}

MainMenu::~MainMenu()
{
  if(startText_)
    delete startText_;

  if(font_)
    delete font_;

  if(texture)
    delete texture;
  
  if(points_)
    delete points_;
  
  if(donkeyName_)
    delete donkeyName_;

  if(exitText_)
    delete exitText_;
}

std::string MainMenu::getCommand()
{
  return command_;
}

void MainMenu::setPoints(sf::Text text)
{
  points_->setString("With: " + (&text)->getString() + " points");
}

void MainMenu::setCommand(std::string command)
{
  if(command == "win")
  {
    startText_->setString("YOU WIN");
    startText_->setPosition(sf::Vector2f(455,255));
    points_->setFillColor(sf::Color::Green);
  }
  if(command == "defeat")
  {
    startText_->setString("YOU DEFEAT");
    startText_->setPosition(sf::Vector2f(430,255));
    startShape_.setFillColor(sf::Color::Red);  
    points_->setFillColor(sf::Color::Red);
  }
  command_ = command;
}

void MainMenu::handleInput()
{
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    movingShape_.setPosition(400,250);
    tmpCom_ = "start";
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
    movingShape_.setPosition(400,350);  
    tmpCom_ = "exit";
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
  {
    setCommand(tmpCom_);  
  }
}

void MainMenu::render(sf::RenderWindow* rw)
{
  handleInput();
  rw->draw(*donkeyName_);
  rw->draw(movingShape_);
  rw->draw(startShape_);
  rw->draw(exitShape_);
  rw->draw(*startText_);
  rw->draw(*exitText_);
  rw->draw(*points_);
}