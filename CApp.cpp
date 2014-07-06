#include "CApp.hpp"

#include <iostream>

CApp::CApp() {
  running = true;
  selected = false;
  toX = toY = fromX = fromY = 0;
}

int CApp::OnExecute() {

  if (!OnInit()) {
    return -1;
  }

  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      OnEvent(event);
    }
    OnLoop();
    OnRender();
    SDL_Delay(200);
  }

  OnCleanup();

  return 0;
}


bool CApp::OnInit() {

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return false;
  }

  win = SDL_CreateWindow("Hello World!",
                                     100, 100, 640, 640,
                                     SDL_WINDOW_SHOWN);
  if (win == nullptr){
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return false;
  }

  surface = SDL_GetWindowSurface(win);
  SDL_FillRect(surface, NULL,
	       SDL_MapRGB(surface->format, 125, 125, 125));
  board.draw(surface);
  SDL_UpdateWindowSurface(win);
  return true;
}

void CApp::OnEvent(SDL_Event& e) {

  // handle quit event
  if (e.type == SDL_QUIT) {
    running = false;
    return;
  }

  // handle mouse events

  if (e.type == SDL_MOUSEBUTTONDOWN) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (selected) {
      toX = x;
      toY = y;
      selected = false;
      board.movePiece(fromX, fromY, toX, toY);
    } else {
      if (board.select(x, y)) {
	fromX = x;
	fromY = y;
	selected = true;
      }
    }
  }
}

void CApp::OnLoop() {}

void CApp::OnRender() {
  board.draw(surface);
  SDL_UpdateWindowSurface(win);
}

void CApp::OnCleanup() {
  SDL_FreeSurface(surface);
  SDL_Quit();
}

int main(int argc, char* argv[]) {
  CApp capp;
  return capp.OnExecute();
}
