#include "Pawn.hpp"

#include "Board.hpp"

using namespace std;

MovesList Pawn::possibleMoves() {
  MovesList pos;

  // TODO account for possible switch in start position
  int mod = color == WHITE ? 1 : -1;

  checkDirection(0, mod, &pos, 2);
  if (y == (7 + mod) % 7)
    pos.push_back(make_pair(x, y + mod * 2));

  if (board.colorAt(x + mod, y + mod) == 1 - color)
    checkDirection(mod, mod, &pos, 2);
  if (board.colorAt(x - mod, y + mod) == 1 - color)
    checkDirection(-mod, mod, &pos, 2);

  return pos;
}

MovesList Pawn::attackedFields() {
  MovesList pos;

  int mod = color == WHITE ? 1 : -1;

  pos.push_back(make_pair(x + 1, y + mod));
  pos.push_back(make_pair(x - 1, y + mod));

  return pos;
}
