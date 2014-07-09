#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL2/SDL.h>
#include "Board.hpp"

class CApp {

private:
  bool running;
  bool selected; // selected a piece to move from
  Board* board;

  // to and from piece locations (in display coordinates)
  int fromX, fromY, toX, toY;

  // surfaces for up and down images
  SDL_Surface* upSurface;
  SDL_Surface* downSurface;

  SDL_Window *win;   // the game window
  SDL_Surface* surface; // surface for the whole game

  bool OnInit();

  void OnEvent(SDL_Event&);

  void OnLoop();

  void OnRender();

  void OnCleanup();

public:

  CApp();
  ~CApp();

  int OnExecute();
};

#endif /* _CAPP_H_ */
