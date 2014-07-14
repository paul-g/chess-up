#include "CApp.hpp"

#include <iostream>
#include <SDL2/SDL_image.h>

using namespace std;

CApp::CApp() {
  running = true;
  selected = false;
  toX = toY = fromX = fromY = 0;
}

CApp::~CApp() {
  delete board;
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
    cout << "SDL_Init Error: " << SDL_GetError() << endl;
    return false;
  }

  win = SDL_CreateWindow("Hello World!",
			 100, 100, 880, 640,
			 SDL_WINDOW_SHOWN);
  if (win == nullptr){
    cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
    SDL_Quit();
    return false;
  }

  //Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
      printf( "SDL_image could not initialize! SDL_image Error: %s\n",
	      IMG_GetError() );
  }

  surface = SDL_GetWindowSurface(win);
  SDL_FillRect(surface, NULL,
	       SDL_MapRGB(surface->format, 125, 125, 125));
  board = new Board(surface);
  board->draw();
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
      if (board->movePiece(fromX, fromY, toX, toY)) {
	// if move was valid update state
	bool check = board->opponentInCheck();
	board->updateToMove();
	if (check) {
	  cout << "Check!" << endl;
	}
      }
    } else {
      if (board->select(x, y)) {
	fromX = x;
	fromY = y;
	selected = true;
      }
    }
  }
}

void CApp::OnLoop() {}

void CApp::OnRender() {
  board->draw();
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
