#include "King.hpp"

#include "Board.hpp"

using namespace std;

MovesList King::possibleMoves() {
  MovesList pos;
  for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++)
      checkDirection(i, j, &pos, 2);
  // TODO check that move is adjacent opponent's king
  return pos;
}
