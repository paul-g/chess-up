#include "Queen.hpp"

MovesList Queen::possibleMoves() {
  MovesList pos;
  for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++)
      checkDirection(i, j, &pos);
  return pos;
}
