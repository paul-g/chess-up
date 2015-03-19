#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.hpp"
#include <SDL2/SDL.h>
#include "resource.hpp"

class Pawn : public Piece {

public:
  Pawn(Board &_board, int color, int x, int y)
      : Piece(_board, PAWN_ID, color, x, y, 
		resource::bpawn(), 
		resource::wpawn()){}

  ~Pawn() { SDL_FreeSurface(surface); }

  MovesList possibleMoves();

  MovesList attackedFields();
};

#endif /* _PAWN_H_ */
