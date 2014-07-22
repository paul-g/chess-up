#include "Rook.hpp"

#include "Board.hpp"

MovesList Rook::possibleMoves() {
  MovesList pos;
  checkDirection(1, 0, &pos);
  checkDirection(-1, 0, &pos);
  checkDirection(0, -1, &pos);
  checkDirection(0, 1, &pos);
  return pos;
}
