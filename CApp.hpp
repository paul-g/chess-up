#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL2/SDL.h>
#include "Board.hpp"

class CApp {

private:
  bool running;
  Board board;

  // surfaces for up and down images
  SDL_Surface* upSurface;
  SDL_Surface* downSurface;

  SDL_Window *win;   // the game window
  SDL_Surface* surface; // surface for the whole game

public:

  CApp();

  int OnExecute();

  bool OnInit();

  void OnEvent(SDL_Event&);

  void OnLoop();

  void OnRender();

  void OnCleanup();

};

#endif /* _CAPP_H_ */
