#include "Pawn.hpp"

#include "Board.hpp"

using namespace std;

MovesList Pawn::possibleMoves() {
  MovesList pos;

  // TODO account for possible switch in start position
  int mod = color == WHITE ? 1 : -1;

  if (y == (7 + mod) % 7)
    pos.push_back(make_pair(x, y + mod * 2));
  pos.push_back(make_pair(x, y + mod));

  int toColor = board.colorAt(x + mod, y + mod);
  if (toColor != NONE && color != toColor)
    pos.push_back(make_pair(x + mod, y + mod));

  toColor = board.colorAt(x - mod, y + mod);
  if (toColor != NONE && color != toColor)
    pos.push_back(make_pair(x - mod, y + mod));

  return pos;
}

MovesList Pawn::attackedFields() {
  MovesList pos;

  int mod = color == WHITE ? 1 : -1;

  pos.push_back(make_pair(x + 1, y + mod));
  pos.push_back(make_pair(x - 1, y + mod));

  return pos;
}
