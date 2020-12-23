#ifndef CHIP_PILE
#define CHIP_PILE

#include <cmath>

class ChipPile {
 public:
  ChipPile();
  ChipPile(int, float);
  int MaxChipsRemovable();
  int MinChipsRemovable();
  int GetNumChipsInPile();
  void RemoveNChips(int);
  
 private:
  int chips_in_pile_;
  float max_chips_removable_percent_;
};

#endif