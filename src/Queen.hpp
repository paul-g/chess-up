#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "Piece.hpp"
#include "resource.hpp"

class Queen : public Piece {

public:
  Queen(Board &_board, int color, int x, int y)
      : Piece(_board, QUEEN_ID, color, x, y, 
		      resource::bqueen(),
		      resource::wqueen()) {}

  ~Queen() { SDL_FreeSurface(surface); }

  MovesList possibleMoves();
};

#endif /* _QUEEN_H_ */
