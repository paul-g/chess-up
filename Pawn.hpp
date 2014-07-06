#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.hpp"
#include <SDL2/SDL.h>

class Pawn : public Piece {

public:
  Pawn(int color) : Piece(color, "black_pawn.bmp", "white_pawn.bmp") {
    firstMove = true;
  }

private:
  bool firstMove;
};


#endif /* _PAWN_H_ */
