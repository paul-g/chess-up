#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "Piece.hpp"

class Bishop : public Piece {

public:

  Bishop(Board& _board, int color, int x, int y) :
    Piece(_board, BISHOP_ID, color, x, y, "black_bishop.bmp", "white_bishop.bmp") {}

  ~Bishop() {
    SDL_FreeSurface(surface);
  }

  std::vector<std::pair<int, int> > validMoves();

private:
  void checkDiagonal(int modx, int mody,
		     std::vector<std::pair<int, int> > *v);

};

#endif /* _BISHOP_H_ */
