#include "King.hpp"

#include "Board.hpp"

using namespace std;

std::vector<std::pair<int, int> > King::possibleMoves() {
  std::vector<std::pair<int, int> > pos;
  for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++)
      checkDirection(i, j, &pos, 2);

  // TODO check that move is not in check
  // TODO check that move is adjacent opponent's king

  cout << pos.size() << endl;
  return pos;
}
