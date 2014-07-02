#include "CApp.hpp"

#include <iostream>

CApp::CApp() {
  running = true;
}

int CApp::OnExecute() {

  if (!OnInit()) {
    return -1;
  }

  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      OnEvent(&event);
    }
    OnLoop();
    OnRender();

    // TODO: remove delay, rune multiple times :D
    SDL_Delay(2000);
    running = false;
  }

  OnCleanup();

  return 0;
}


bool CApp::OnInit() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_Window *win = SDL_CreateWindow("Hello World!",
                                     100, 100, 640, 480,
                                     SDL_WINDOW_SHOWN);
  if (win == nullptr){
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return false;
  }

  surface = SDL_GetWindowSurface(win);
  SDL_FillRect(surface, NULL,
               SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(win);

  return true;
}

void CApp::OnEvent(SDL_Event* Event) {}

void CApp::OnLoop() {}

void CApp::OnRender() {}

void CApp::OnCleanup() {}

int main(int argc, char* argv[]) {
  CApp capp;
  return capp.OnExecute();
}
