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
      OnEvent(event);
    }
    OnLoop();
    OnRender();
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
                                     100, 100, 640, 480,
                                     SDL_WINDOW_SHOWN);
  if (win == nullptr){
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return false;
  }

  surface = SDL_GetWindowSurface(win);
  downSurface = SDL_LoadBMP("hello_world.bmp");
  upSurface = SDL_LoadBMP("x.bmp");
  if (downSurface == nullptr || upSurface == nullptr) {
    std::cout << "Unable to load image for load screen" << std::endl;
    return false;
  }

  SDL_BlitSurface(downSurface, NULL, surface, NULL);
  SDL_UpdateWindowSurface(win);

  return true;
}

void CApp::OnEvent(SDL_Event& e) {

  if (e.type == SDL_QUIT) {
    running = false;
  } else if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
    case SDLK_UP:
      SDL_BlitSurface(upSurface, NULL, surface, NULL);
      break;
    case SDLK_DOWN:
      SDL_BlitSurface(downSurface, NULL, surface, NULL);
      break;
    default:
      std::cout << "Key Not Supported!" << std::endl;
    }
    SDL_UpdateWindowSurface(win);
  }
}

void CApp::OnLoop() {}

void CApp::OnRender() {}

void CApp::OnCleanup() {
  SDL_FreeSurface(surface);
  SDL_Quit();
}

int main(int argc, char* argv[]) {
  CApp capp;
  return capp.OnExecute();
}
