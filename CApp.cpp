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
  }

  OnCleanup();

  return 0;
}


bool CApp::OnInit() {
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    return false;

  // TODO: this seems outdated in SDL 2.0
  // surface =  SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  // if(!surface)
  //   return false;

  return true;}

void CApp::OnEvent(SDL_Event* Event) {}

void CApp::OnLoop() {}

void CApp::OnRender() {}

void CApp::OnCleanup() {}

int main(int argc, char* argv[]) {

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window *win = SDL_CreateWindow("Hello World!",
				     100, 100, 640, 480,
				     SDL_WINDOW_SHOWN);
  if (win == nullptr){
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  return 0;
}
