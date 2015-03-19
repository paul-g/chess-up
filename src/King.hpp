#ifndef _KING_H_
#define _KING_H_

#include "Piece.hpp"
#include "resource.hpp"

class King : public Piece {

public:
  King(Board &_board, int color, int x, int y)
      : Piece(_board, KING_ID, color, x, y, 
	      resource::bking(),
              resource::wking()) {}

  ~King() { SDL_FreeSurface(surface); }

  MovesList possibleMoves();
};

#endif /* _KING_H_ */
