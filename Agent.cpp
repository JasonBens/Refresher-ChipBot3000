#include "Agent.h"

Agent::Agent(std::string name, bool is_bot) : name_(name), is_bot_(is_bot) {}

int Agent::GetNumRemovedChips(int min_chips, int max_chips) {
  if (!IsBot()) {
    std::cout << "Number of chips to remove: ";
    int removed_chips;
    std::cin >> removed_chips;
    return removed_chips;
  }
  else {
    if (max_chips-min_chips > 0) {
      return rand() % (max_chips-min_chips) + min_chips;
    }
    else {
      return 1;
    }
  }
}

bool Agent::IsBot() {
  return is_bot_;
}

std::string Agent::GetName() {
  return name_;
}