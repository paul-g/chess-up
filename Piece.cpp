#include "Piece.hpp"

void Piece::draw(SDL_Surface* srcsurf, int bx, int by) {
  SDL_Rect rect;
  rect.x = toDispX(bx);
  rect.y = toDispY(by);
  rect.w = 80;
  rect.h = 80;
  SDL_BlitSurface(this->surface, NULL, srcsurf, &rect);
}

void Piece::setTransparent(SDL_Surface* surface) {
  SDL_SetColorKey(surface,
                  SDL_TRUE,
                  SDL_MapRGB(surface->format, 0, 255, 0) );
}

SDL_Surface* Piece::loadPiece(std::string path) {
  SDL_Surface* s = SDL_LoadBMP(path.c_str());
  setTransparent(s);
  return s;
}
