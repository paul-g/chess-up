#ifndef _BOARD_H_
#define _BOARD_H_

#include <SDL2/SDL.h>

class Board {
public:
  Board() {}

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

    return true;
  }

};


#endif /* _BOARD_H_ */
