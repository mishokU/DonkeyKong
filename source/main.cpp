#include "Game.hpp"

int main()
{
  Game* game = new Game();
  
  game->setUpSystem("Donkey Kong",1000,600);
  
  while(game->loop());
  
  delete game;
  
  return 0;
}
