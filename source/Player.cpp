#include <iostream>
#include "Player.hpp"

Player::Player(sf::Texture& image)
{
  sprite_.setTexture(image);
  rect_ = sf::FloatRect(10*16,30*16,12,17);
  sprite_.setScale(2,2);
  jumpBuffer_ = new sf::SoundBuffer();
  jumpBuffer_->loadFromFile("jump.ogg");
  jump_ = new sf::Sound();
  jump_->setBuffer(*jumpBuffer_);
  dx_=dy_=0.1;
  health_ = 1000;
  currentFrame_ = 0;
  stairs_ = false;
  direction_ = false;
  onGround_ = false;
  weapon_ = false;
  buttonPressed_ = true;
  hitPrincess_ = false;
  showName_ = false;
}

Player::~Player()
{
  if(jump_)
    delete jump_;

  if(jumpBuffer_)
    delete jumpBuffer_;
}

void Player::handleInput()
{
  if(!spaceHold_)
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
    {
      dx_ = -0.1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
    {
      dx_ = 0.1;
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
  {
    if(onGround_)
    { 
      if(!stairs_) jump_->play();
      dy_ = -0.20;
    }
    if(stairs_)
    {
      dy_ = -0.05;
    }
  }
  else
  {
    if(weapon_)
    {
      if(direction_)
        sprite_.setTextureRect(sf::IntRect(18,234,-17,25));
      else
        sprite_.setTextureRect(sf::IntRect(1,234,17,27));
    }
    else
    {
      if (direction_)
      {
        sprite_.setTextureRect(sf::IntRect(13,204,-14,17));
      }
      else
      {
        sprite_.setTextureRect(sf::IntRect(1,204,14,17));
      }
    }
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
    if(stairs_)
    {
      dy_ += 0.05;
    }
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
  {
    if(weapon_)
    {
      spaceHold_ = true;
      if(direction_)
      {
        if(rect_.left / PixelPerCell < Width - 5) rect_.left += 5;  
        sprite_.setTextureRect(sf::IntRect(106,244,-29,18));
      }
      else
      {
        if(rect_.left / PixelPerCell > 5) rect_.left -= 5;
        sprite_.setTextureRect(sf::IntRect(77,244,29,18));
      }
    }
  }
  else
  {
    spaceHold_ = false;
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
  {
    weapon_ = false;
  }
  if(onGround_) onGround_ = false;
  if(stairs_) stairs_ = false;
}

void Player::update(float time)
{
  handleInput();
  
  rect_.left += dx_ * time;	
  collision(0);

  if (!onGround_ && !stairs_) dy_=dy_+0.0005*time;
  rect_.top += dy_*time;
  onGround_ = false;
  collision(1);

  currentFrame_ += 0.005*time;
  if(stairs_)
  {
    if (currentFrame_ > ClimbFrames) currentFrame_ -= ClimbFrames;
    
    if(dy_ < 0)
       sprite_.setTextureRect(sf::IntRect(16*int(currentFrame_)+56,204,16,18));
    else
       sprite_.setTextureRect(sf::IntRect(16+55,205,17,18));
    
    onGround_ = true;
    dy_ = 0;
  }
  else
  {
    if(weapon_)
    {
      if (currentFrame_ > 4) currentFrame_ -= 4;
      if(dx_ > 0)
      {
        direction_ = true;
        sprite_.setTextureRect(sf::IntRect(17*int(currentFrame_)+17,234,-17,27));
      }
      if( dx_ < 0)
      {
        direction_ = false;
        sprite_.setTextureRect(sf::IntRect(17*int(currentFrame_),234,17,27));
      }
    }
    else
    {
      if (currentFrame_ > WalkFrames) currentFrame_ -= WalkFrames;
      if (dx_ > 0)
      {
          direction_ = true;
          sprite_.setTextureRect(sf::IntRect(15*int(currentFrame_)+15,204,-15,17));
      }
      if (dx_ < 0)
      {
          direction_ = false;
          sprite_.setTextureRect(sf::IntRect(15*int(currentFrame_),204,15,17));
      }
    }
  }
  if(spaceHold_)
    sprite_.setPosition(rect_.left, rect_.top);
  else if(weapon_)
    sprite_.setPosition(rect_.left, rect_.top - 20);
  else
    sprite_.setPosition(rect_.left - 5, rect_.top);
  dx_=0;
}

void Player::render(sf::RenderWindow* rw)
{
  rw->draw(sprite_);
}

void Player::collision(int dir)
{
  for (int i = rect_.top/PixelPerCell ; i<(rect_.top+rect_.height * 2)/PixelPerCell; i++)
  {
    for (int j = rect_.left/PixelPerCell; j<(rect_.left+rect_.width * 2)/PixelPerCell; j++)
    { 
      if (tileMap[i][j]=='#' || tileMap[i][j]=='@' || tileMap[i][j] == 'H') 
      {
        if ((dx_>0) && (dir==0))
        {
           rect_.left =  j*PixelPerCell -  rect_.width * 2; 
        }
        if ((dx_<0) && (dir==0))
        {
           rect_.left =  j*PixelPerCell + PixelPerCell;
        }
        if ((dy_>0) && (dir==1))
        {
          rect_.top =   i*PixelPerCell -  rect_.height * 2;
          dy_=0;
          onGround_ = true;
          stairs_ = false;
        }
        if ((dy_<0) && (dir==1) && !(tileMap[i][j] == 'H' && buttonPressed_))
        {
          rect_.top = i*PixelPerCell + PixelPerCell;
          dy_=0;
        }
      }
      if((tileMap[i][j] == 'S' || tileMap[i][j] == '$') && !stairs_)
      {
        stairs_ = true;
      }
      
      if(tileMap[i][j] == 'W' && !weapon_)
      {
        weapon_ = true;
      }
      if(tileMap[i][j] == 'P')
      {
        hitPrincess_ = true;
      }
      if(tileMap[i][j] == 'E')
      {
        showName_ = true;
      }
    }
  }
}