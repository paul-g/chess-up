#ifndef _BOARD_H_
#define _BOARD_H_

#include <SDL2/SDL.h>

class Board {
public:
  Board() {
    bPawnS = SDL_LoadBMP("black_pawn.bmp");
    SDL_SetColorKey(bPawnS,
		    SDL_TRUE,
		    SDL_MapRGB(bPawnS->format, 0, 255, 0) );
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

    drawPawn(surface);

    return true;
  }

private:

  void drawPawn(SDL_Surface* surface) {
    SDL_Rect rect;
    rect.x = 80;
    rect.y = 80;
    rect.w = 80;
    rect.h = 80;
    SDL_BlitSurface(bPawnS, NULL, surface, &rect);
  }

  SDL_Surface* bPawnS;
};


#endif /* _BOARD_H_ */
