#ifndef _BOARD_H_
#define _BOARD_H_

#include <SDL2/SDL.h>
#include <string>
#include <iostream>


using namespace std;

class Board {
public:
  Board() {
    bPawnS = loadPiece("white_pawn.bmp");
    wPawnS = loadPiece("black_pawn.bmp");
  }

  ~Board() {
    // TODO free pawn surface
  }

  bool draw(SDL_Surface* surface) {
    for (int j = 0; j <= 640; j+= 80) {
      int start = (j / 80) % 2 == 0 ? 0 : 80;
      for (int i = start; i <= 640; i+= 160) {
        SDL_Rect rect;
        rect.x = i;
        rect.y = j;
        rect.w = 80;
        rect.h = 80;
        SDL_FillRect(surface, &rect,
                     SDL_MapRGB(surface->format, 255, 255, 255));
      }
    }

    for (int i = 0; i < 8; i++) {
      drawPiece(surface, i, 1, bPawnS);
      drawPiece(surface, i, 6, wPawnS);
    }

    return true;
  }

private:

  void drawPiece(SDL_Surface* surface, int bx, int by, SDL_Surface* piece) {
    SDL_Rect rect;
    rect.x = toDispX(bx);
    rect.y = toDispY(by);
    rect.w = 80;
    rect.h = 80;
    SDL_BlitSurface(piece, NULL, surface, &rect);
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

  int toDispX(int bx) {
    return 80 * bx;
  }

  int toDispY(int by) {
    return 80 * by;
  }

  SDL_Surface* bPawnS;
  SDL_Surface* wPawnS;
};


#endif /* _BOARD_H_ */
