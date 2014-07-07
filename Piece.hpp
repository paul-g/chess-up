#ifndef _PIECE_H_
#define _PIECE_H_

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <vector>

const int WHITE = 0;
const int BLACK = 1;

class Piece {

public:

  Piece(int _color,
	int _x,
	int _y,
	std::string blackImg,
	std::string whiteImg) : x(_x), y(_y), color(_color) {
    this->surface = color == BLACK ? loadPiece(blackImg) : loadPiece(whiteImg);
  }

  virtual std::vector<std::pair<int, int> > validMoves() = 0;

  virtual ~Piece() {}

  void draw(SDL_Surface* srcsurf, int bx, int by) {
    SDL_Rect rect;
    rect.x = toDispX(bx);
    rect.y = toDispY(by);
    rect.w = 80;
    rect.h = 80;
    SDL_BlitSurface(this->surface, NULL, srcsurf, &rect);
  }

  void move(int toX, int toY) {
    x = toX;
    y = toY;
  }

protected:
  int toDispX(int bx) {
    return 80 * bx;
  }

  int toDispY(int by) {
    return 80 * by;
  }

  void setTransparent(SDL_Surface* surface) {
    SDL_SetColorKey(surface,
		    SDL_TRUE,
		    SDL_MapRGB(surface->format, 0, 255, 0) );
  }

  SDL_Surface* loadPiece(std::string path) {
    SDL_Surface* s = SDL_LoadBMP(path.c_str());
    setTransparent(s);
    return s;
  }

  SDL_Surface* surface;

  int x, y;
  int color;
};


#endif /* _PIECE_H_ */
