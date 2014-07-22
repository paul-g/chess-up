#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.hpp"
#include <SDL2/SDL.h>

class Pawn : public Piece {

public:
  Pawn(Board &_board, int color, int x, int y)
      : Piece(_board, PAWN_ID, color, x, y, "black_pawn.png",
              "white_pawn.png") {}

  ~Pawn() { SDL_FreeSurface(surface); }

  MovesList possibleMoves();

  MovesList attackedFields();
};

#endif /* _PAWN_H_ */
