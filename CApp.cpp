#include "CApp.hpp"

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


bool CApp::OnInit() {return true;}

void CApp::OnEvent(SDL_Event* Event) {}

void CApp::OnLoop() {}

void CApp::OnRender() {}

void CApp::OnCleanup() {}

int main(int argc, char* argv[]) {
  CApp theApp;

  return theApp.OnExecute();
}
