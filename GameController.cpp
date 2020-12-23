#include "GameController.h"

GameController::GameController() {}

void GameController::InitPlayers() {
  int num_players = AskNumPlayers();
  
  for (int i = 0; i < num_players; i++) {
    agents_.push_back(Agent(AskPlayerName(), false));
    num_participants_++;
  }
}

int GameController::AskNumPlayers() {
  bool is_invalid_num_players = true;
  int num_players = -1;
  while (is_invalid_num_players) { 
    std::cout << "Enter number of players: " << std::endl;
    std::cin >> num_players;
    if (num_players >= 0)
      is_invalid_num_players = false;
  }
  return num_players;
}

std::string GameController::AskPlayerName() {
  std::string player_name;
  std::cout << "Player, what is your name?" << std::endl;
  std::cin >> player_name;
  player_names_.push_back(player_name);
  return player_name;
}

void GameController::InitBots() {
  int num_bots = AskNumBots();
  for (int i = 0; i < num_bots; i++) {
    agents_.push_back(Agent("Computer" + std::to_string(i), true));
    num_participants_++;
  }
}

int GameController::AskNumBots() {
  bool is_invalid_num_bots = true;
  int num_bots = -1;

  while (is_invalid_num_bots)
  { 
    std::cout << "Enter number of bots: " << std::endl;
    std::cin >> num_bots;
    if (num_bots >= 0)
      is_invalid_num_bots = false;
  }
  return num_bots;
}

void GameController::InitGame() {
  chip_pile_ = ChipPile(kMaxChips, kMaxPercentChipsRemovable);
  current_turn_ = 0;
}

bool GameController::IsGameOver() {
  return (chip_pile_.GetNumChipsInPile() <= 1);
}

int GameController::AskAgentForChips(Agent* agent) {
  if (agent->IsBot()) {
    std::cout << agent->GetName() << ", " << chip_pile_.GetNumChipsInPile() << " chips remain.  You may remove up to " << chip_pile_.MaxChipsRemovable() << " chips.  Destroy " << player_names_[rand() % player_names_.size()] << "." << std::endl;
    std::cout << std::endl;
  }
  else {
    std::cout << agent->GetName() << ", " << chip_pile_.GetNumChipsInPile() << " chips remain.  You may remove up to " << chip_pile_.MaxChipsRemovable() << " chips.  Choose wisely." << std::endl;
    std::cout << std::endl;
  }

  int removed_chips = 0;
  while (removed_chips == 0) {
    removed_chips = agent->GetNumRemovedChips(chip_pile_.MinChipsRemovable(), chip_pile_.MaxChipsRemovable());
    if (removed_chips < chip_pile_.MinChipsRemovable() || removed_chips > chip_pile_.MaxChipsRemovable()) {
      removed_chips = 0;
      TauntAgentInvalidNumChips();
    }
  }
  return removed_chips;
}

void GameController::TauntAgentInvalidNumChips() {
  std::cout << "Fool!  You must select between 1 and " << chip_pile_.MaxChipsRemovable() << " chips." << std::endl;
  std::cout << std::endl;
}

void GameController::PostAgentChipsTaken(std::string player_name, int removed_chips, bool is_bot) {
  if (is_bot) {
    std::cout << player_name << " removed " << removed_chips << " chips.  Devious." << std::endl;
    std::cout << std::endl;
  }
  else {
    std::cout << player_name << " removed " << removed_chips << " chips.  Are you even trying?" << std::endl;
    std::cout << std::endl;
  }
}

void GameController::TauntLoserAgent(std::string player_name, bool is_bot) {
  if(is_bot) {
    std::cout << "You have defeated " << player_name << ".  This is unthinkable." << std::endl;
  }
  else {
    std::cout << player_name << ", you must remove the remaining chip.  Pathetic." << std::endl;
  }
}

bool GameController::GetAgentPlayAgain() {
  char player_choice = 'n';
  std::cout << "Do you want to play again?  [Y/n]: ";
  std::cin >> player_choice;
  if (std::toupper(player_choice) == 'Y') {
    return true;
  }
  return false;
}

Agent* GameController::GetCurrentAgent() {
  return &agents_[current_turn_ % num_participants_];
}

Agent* GameController::GetLoserAgent() {
  return &agents_[current_turn_ % num_participants_];
}

void GameController::ExecuteNextTurn() {
  Agent* curr_agent = GetCurrentAgent();
  int max_chips = chip_pile_.MaxChipsRemovable();
  int min_chips = chip_pile_.MinChipsRemovable();
  
  int removed_chips = AskAgentForChips(curr_agent);
  
  chip_pile_.RemoveNChips(removed_chips);
  current_turn_++;
}

bool GameController::playGame() {
  
  InitGame();

  while (!IsGameOver()) {
    ExecuteNextTurn();
  }
  Agent* loser = GetLoserAgent();
  TauntLoserAgent(loser->GetName(), loser->IsBot());

  std::ofstream ofResults;
  ofResults.open("results.txt", std::ios::app);
  ofResults << loser->GetName() << " lost in " << current_turn_ << " turns." << std::endl;
  ofResults.close();

  return GetAgentPlayAgain();  
}