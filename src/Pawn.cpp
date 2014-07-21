#include "Pawn.hpp"

#include "Board.hpp"

std::vector<std::pair<int, int> > Pawn::possibleMoves() {
  std::vector<std::pair<int, int> > pos;

  // TODO account for possible switch in start position
  int mod = color == WHITE ? 1 : -1;

  if (y == (7 + mod) % 7)
    pos.push_back(std::make_pair(x, y + mod * 2));
  pos.push_back(std::make_pair(x, y + mod));

  int toColor = board.colorAt(x + mod, y + mod);
  if (toColor != NONE && color != toColor)
    pos.push_back(std::make_pair(x + mod, y + mod));

  toColor = board.colorAt(x - mod, y + mod);
  if (toColor != NONE && color != toColor)
    pos.push_back(std::make_pair(x - mod, y + mod));

  return pos;
}
