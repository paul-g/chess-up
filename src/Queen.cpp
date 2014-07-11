#include "Queen.hpp"
#include <vector>

using namespace std;

vector<pair<int, int> > Queen::validMoves() {
  vector<pair<int, int> > pos;
  for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++)
      checkDirection(i, j, &pos);
  return pos;
}
