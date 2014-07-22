#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "Piece.hpp"

class Knight : public Piece {

public:
  Knight(Board &_board, int color, int x, int y)
      : Piece(_board, KNIGHT_ID, color, x, y, "black_knight.png",
              "white_knight.png") {}

  ~Knight() { SDL_FreeSurface(surface); }

  MovesList possibleMoves();
};

#endif /* _KNIGHT_H_ */
