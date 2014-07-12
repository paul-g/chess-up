#include "Knight.hpp"

#include "Board.hpp"

using namespace std;

std::vector<std::pair<int, int> > Knight::validMoves() {
  std::vector<std::pair<int, int> > pos;

  for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++) {
      if (i == 0 || j == 0)
	continue;
      int tox = x + i * 2;
      int toy = y + j;
      if (canMove(tox, toy))
	pos.push_back(make_pair(tox, toy));
      tox = x + i;
      toy = y + j * 2;
      if (canMove(tox, toy))
	pos.push_back(make_pair(tox, toy));
    }

  cout << pos.size() << endl;
  return pos;
}
