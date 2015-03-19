#ifndef _ROOK_H_
#define _ROOK_H_

#include "Piece.hpp"
#include "resource.hpp"

class Rook : public Piece {

public:
  Rook(Board &_board, int color, int x, int y)
      : Piece(_board, ROOK_ID, color, x, y, 
		      resource::brook(),
		      resource::wrook()) {}

  ~Rook() { SDL_FreeSurface(surface); }

  MovesList possibleMoves();
};

#endif /* _ROOK_H_ */
