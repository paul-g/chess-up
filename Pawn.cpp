#include "Pawn.hpp"

std::vector<std::pair<int, int> > Pawn::validMoves() {
  std::vector<std::pair<int, int> > pos;

  // TODO check if squares are occupied
  // first move can jump 2
  if (color == WHITE) {
    if (y == 1)
      pos.push_back(std::make_pair(x, y + 2));
    pos.push_back(std::make_pair(x, y + 1));
  } else {
    if (y == 6)
      pos.push_back(std::make_pair(x, y - 2));
    pos.push_back(std::make_pair(x, y - 1));
  }

  // TODO add diagonal capture movement
  std::cout << "Pos: " << pos.size() << std::endl;
  return pos;
}
