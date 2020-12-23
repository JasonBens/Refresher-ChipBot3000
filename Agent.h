#ifndef AGENT
#define AGENT

#include <string>
#include <iostream>

class Agent {
 public:
  Agent(std::string, bool);
  int GetNumRemovedChips(int, int);
  bool IsBot();
  std::string GetName();
  
 private:
  std::string name_;
  bool is_bot_;
};

#endif