#include "Bishop.hpp"

#include "Board.hpp"

using namespace std;

MovesList Bishop::possibleMoves() {
  MovesList pos;
  checkDirection(1, 1, &pos);
  checkDirection(-1, 1, &pos);
  checkDirection(1, -1, &pos);
  checkDirection(-1, -1, &pos);
  return pos;
}
