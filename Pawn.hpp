#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.hpp"
#include <SDL2/SDL.h>
#include <vector>

class Pawn : public Piece {

public:
  Pawn(int color, int x, int y) :
    Piece(color, x, y, "black_pawn.bmp", "white_pawn.bmp")
  {}

  ~Pawn() {
    SDL_FreeSurface(surface);
  }
};


#endif /* _PAWN_H_ */
