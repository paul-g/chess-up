#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "Piece.hpp"
#include "resource.hpp"

class Knight : public Piece {

public:
  Knight(Board &_board, int color, int x, int y)
      : Piece(_board, KNIGHT_ID, color, x, y, 
		      resource::bknight(),
		      resource::wknight()) {}

  ~Knight() { SDL_FreeSurface(surface); }

  MovesList possibleMoves();
};

#endif /* _KNIGHT_H_ */
