#include "Agent.h"
#include "ChipPile.h"
#include "GameController.h"
#include <ctime>
#include <cmath>

// A simple game where you remove chips from a pile.  The loser is whoever removes the last one.

int main() {
  
  srand(time(0));

  GameController game_controller;
  
  game_controller.InitPlayers();
  game_controller.InitBots();
   
  while(game_controller.playGame());

  return 0;
}