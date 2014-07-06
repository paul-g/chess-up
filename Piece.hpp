#ifndef _PIECE_H_
#define _PIECE_H_

#include <SDL2/SDL.h>
#include <string>

const int WHITE = 0;
const int BLACK = 1;

class Piece {

public:
  Piece() {}
  virtual ~Piece() {}

  virtual void draw() = 0;

protected:
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

};


#endif /* _PIECE_H_ */
