#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "Piece.hpp"

class Queen : public Piece {

public:
  Queen(Board &_board, int color, int x, int y)
      : Piece(_board, QUEEN_ID, color, x, y, "black_queen.png",
              "white_queen.png") {}

  ~Queen() { SDL_FreeSurface(surface); }

  std::vector<std::pair<int, int> > possibleMoves();
};

#endif /* _QUEEN_H_ */
