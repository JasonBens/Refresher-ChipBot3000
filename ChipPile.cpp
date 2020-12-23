#include "ChipPile.h"

ChipPile::ChipPile() {}

ChipPile::ChipPile(int initial_num_chips, float max_chips_removable_percent)
    : chips_in_pile_(initial_num_chips), max_chips_removable_percent_(max_chips_removable_percent) {}


int ChipPile::MaxChipsRemovable() {
  return static_cast <int> (floor(chips_in_pile_ * max_chips_removable_percent_));
}

int ChipPile::MinChipsRemovable() {
  return 1;
}

int ChipPile::GetNumChipsInPile() {
  return chips_in_pile_;
}

void ChipPile::RemoveNChips(int n_chips_removed) {
  chips_in_pile_ = chips_in_pile_ - n_chips_removed;
}