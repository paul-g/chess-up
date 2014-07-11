#include "Rook.hpp"

#include "Board.hpp"

using namespace std;

std::vector<std::pair<int, int> > Rook::validMoves() {
  std::vector<std::pair<int, int> > pos;
  checkDirection(1, 0, &pos);
  checkDirection(-1, 0, &pos);
  checkDirection(0, -1, &pos);
  checkDirection(0, 1, &pos);
  cout << pos.size() << endl;
  return pos;
}
