#include "barrels.hpp"

Barrel::Barrel(sf::Texture& image)
{
  sprite_.setTexture(image);
  sprite_.setScale(2,2);
  rect_      = sf::FloatRect(9*16,6*16,13,12);
  dx_ = dy_  = 0.1;
  direction_ = true;
  onGround_  = false;
  stop_      = false;
  speed_ = 0.01;
  tileYpos_  = 75;
  currentFrame_ = 0;
}


void Barrel::update(float time)
{

  dx_ = (direction_) ? (dx_ + speed_*time) : (dx_ - speed_*time);
  rect_.left += dx_ * time;	
  collision(0);

  if (!onGround_) dy_ +=0.0005*time;
  rect_.top += dy_*time;
  onGround_ = false;
  collision(1);

  currentFrame_ += 0.005*time;
  if (currentFrame_ > 3) currentFrame_ -=3;

  sprite_.setTextureRect(sf::IntRect(13*int(currentFrame_)+244,tileYpos_,13,12));
  sprite_.setPosition(rect_.left,rect_.top);
  
  dx_=0;
}

void Barrel::render(sf::RenderWindow* rw)
{
  rw->draw(sprite_);
}

void Barrel::collision(int dir)
{
  for (int i = rect_.top/16 ; i<(rect_.top+rect_.height * 2)/16; i++)
  {
    for (int j = rect_.left/16; j<(rect_.left+rect_.width * 2)/16; j++)
    { 
      if (tileMap[i][j]=='#' || tileMap[i][j] == '@' || tileMap[i][j] == '$') 
      { 
        if ((dx_>0) && (dir==0))
        {
           if(tileMap[i][j] == '@') direction_ = false;
           rect_.left =  j*16 - rect_.width * 2; 
        }
        if ((dx_<0) && (dir==0))
        {
           if(tileMap[i][j] == '@') direction_ = true;
           rect_.left =  j*16 + 16;
        }
        if ((dy_>0) && (dir==1))
        { 
          rect_.top =   i*16 - rect_.height * 2;
          dy_=0;
          onGround_ = true;
        }
        if ((dy_<0) && (dir==1))
        { 
          rect_.top = i*16 + 16;
          dy_=0;
        }
      }
      if(tileMap[i][j] == 'X')
      {
        stop_ = true;
      }
    }
  }
}
