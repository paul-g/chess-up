#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "Piece.hpp"
#include "resource.hpp"

class Bishop : public Piece {

public:
  Bishop(Board &_board, int color, int x, int y)
      : Piece(_board, BISHOP_ID, color, x, y, 
		resource::bbishop(),
              	resource::wbishop()) {}

  ~Bishop() { SDL_FreeSurface(surface); }

  MovesList possibleMoves();
};

#endif /* _BISHOP_H_ */
