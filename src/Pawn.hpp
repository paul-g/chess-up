#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.hpp"
#include <SDL2/SDL.h>
#include <vector>

class Pawn : public Piece {

public:
  Pawn(Board &_board, int color, int x, int y)
      : Piece(_board, PAWN_ID, color, x, y, "black_pawn.png",
              "white_pawn.png") {}

  ~Pawn() { SDL_FreeSurface(surface); }

  std::vector<std::pair<int, int> > validMoves();
};

#endif /* _PAWN_H_ */
