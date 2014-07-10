#include "Bishop.hpp"

#include "Board.hpp"

using namespace std;

std::vector<std::pair<int, int> > Bishop::validMoves() {
  std::vector<std::pair<int, int> > pos;
  checkDiagonal(1, 1, &pos);
  checkDiagonal(-1, 1, &pos);
  checkDiagonal(1, -1, &pos);
  checkDiagonal(-1, -1, &pos);
  cout << pos.size() << endl;

  return pos;
}

void
Bishop::checkDiagonal(int modx, int mody,
		      std::vector<std::pair<int, int> > *v) {

  for (int i = 1; i < 8; i++) {

    int tox = x + modx * i;
    int toy = y + mody * i;

    if (tox > 7 || toy > 7 ||
        tox < 0 || toy < 0)
      continue;

    int toColor = board.colorAt(tox, toy);

    if (toColor == color)
      break;

    v->push_back(std::make_pair(tox, toy));
    cout << "Adding pair " << tox << " " << toy << endl;
    if (toColor != NONE) {
      cout << "Different color, stopping" << endl;
      break;
    }
  }

}
