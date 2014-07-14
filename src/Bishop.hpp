#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "Piece.hpp"

class Bishop : public Piece {

public:
  Bishop(Board &_board, int color, int x, int y)
      : Piece(_board, BISHOP_ID, color, x, y, "black_bishop.png",
              "white_bishop.png") {}

  ~Bishop() { SDL_FreeSurface(surface); }

  std::vector<std::pair<int, int> > validMoves();
};

#endif /* _BISHOP_H_ */
