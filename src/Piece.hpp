#ifndef _PIECE_H_
#define _PIECE_H_

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <vector>

class Board;

const int WHITE = 0;
const int BLACK = 1;
const int NONE = 2;

class Piece {

public:

  Piece(Board& _board,
        int _color,
        int _x,
        int _y,
        std::string blackImg,
        std::string whiteImg) : x(_x), y(_y), color(_color), board(_board) {
    this->surface = color == BLACK ? loadPiece(blackImg) : loadPiece(whiteImg);
  }

  virtual std::vector<std::pair<int, int> > validMoves() = 0;

  virtual ~Piece() {}

  void draw(SDL_Surface* srcsurf, int bx, int by);

  void move(int toX, int toY) {
    x = toX;
    y = toY;
  }

  inline int getColor() const {
    return color;
  }

protected:
  inline int toDispX(int bx) const {
    return 80 * bx;
  }

  inline int toDispY(int by) const {
    return 80 * by;
  }

  void setTransparent(SDL_Surface* surface);
  SDL_Surface* loadPiece(std::string path);

  SDL_Surface* surface;
  int x, y;
  int color;
  Board& board;
};


#endif /* _PIECE_H_ */