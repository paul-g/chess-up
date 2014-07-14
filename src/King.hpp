#ifndef _KING_H_
#define _KING_H_

#include "Piece.hpp"

class King : public Piece {

public:
  King(Board &_board, int color, int x, int y)
      : Piece(_board, KING_ID, color, x, y, "black_king.png",
              "white_king.png") {}

  ~King() { SDL_FreeSurface(surface); }

  std::vector<std::pair<int, int> > validMoves();
};

#endif /* _KING_H_ */
