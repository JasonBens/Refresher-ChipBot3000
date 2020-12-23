#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ChipPile.h"
#include "Agent.h"

class GameController {
 public:
  GameController();
  void InitPlayers();
  void InitBots();
  void InitGame();
  bool playGame();
  void ExecuteNextTurn();
 
 private:
  ChipPile chip_pile_;
  const int kMaxChips = 100;
  const float kMaxPercentChipsRemovable = 0.5;
  int current_turn_ = 0;
  int num_participants_ = 0;
  std::vector<Agent> agents_;
  std::vector<std::string> player_names_;
  int AskNumPlayers();
  int AskNumBots();
  std::string AskPlayerName();
  Agent* GetCurrentAgent();
  Agent* GetLoserAgent();
  int AskAgentForChips(Agent*);
  void PostAgentChipsTaken(std::string, int, bool);
  void TauntAgentInvalidNumChips();
  void TauntLoserAgent(std::string, bool);
  bool GetAgentPlayAgain();
  bool IsGameOver();
};

#endif