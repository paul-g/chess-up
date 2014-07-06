#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.hpp"
#include <SDL2/SDL.h>

class Pawn : public Piece {

public:
  Pawn(int color) {
    if (color == WHITE)
      surface = loadPiece("white_pawn.bmp");
    else
      surface = loadPiece("black_pawn.bmp");
    firstMove = true;
  }

private:
  SDL_Surface* surface;
  bool firstMove;

};


#endif /* _PAWN_H_ */
