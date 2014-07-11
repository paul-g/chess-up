#ifndef _ROOK_H_
#define _ROOK_H_

#include "Piece.hpp"

class Rook : public Piece {

public:

  Rook(Board& _board, int color, int x, int y) :
    Piece(_board, ROOK_ID, color, x, y, "black_rook.png", "white_rook.png") {}

  ~Rook() {
    SDL_FreeSurface(surface);
  }

  std::vector<std::pair<int, int> > validMoves();

};

#endif /* _ROOK_H_ */
