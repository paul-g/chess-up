#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.hpp"
#include <SDL2/SDL.h>
#include <vector>

class Pawn : public Piece {

public:
  Pawn(int color, int x, int y) :
    Piece(color, x, y, "black_pawn.bmp", "white_pawn.bmp") {
    firstMove = true;
  }

  std::vector<std::pair<int, int> > validMoves() {
    std::vector<std::pair<int, int> > pos;

    // TODO check if squares are occupied
    // first move can jump 2
    if (color == WHITE) {
      if (y == 1)
	pos.push_back(std::make_pair(x, y + 2));
      pos.push_back(std::make_pair(x, y + 1));
    } else {
      if (y == 6)
	pos.push_back(std::make_pair(x, y - 2));
      pos.push_back(std::make_pair(x, y - 1));
    }

    // TODO add diagonal capture movement
    std::cout << "Pos: " << pos.size() << std::endl;
    return pos;
  }

  ~Pawn() {
    SDL_FreeSurface(surface);
  }

private:
  bool firstMove;
};


#endif /* _PAWN_H_ */
