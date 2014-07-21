#include "Bishop.hpp"

#include "Board.hpp"

using namespace std;

std::vector<std::pair<int, int> > Bishop::possibleMoves() {
  std::vector<std::pair<int, int> > pos;
  checkDirection(1, 1, &pos);
  checkDirection(-1, 1, &pos);
  checkDirection(1, -1, &pos);
  checkDirection(-1, -1, &pos);
  cout << pos.size() << endl;

  return pos;
}
