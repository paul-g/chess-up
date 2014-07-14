#include "Piece.hpp"

#include <SDL2/SDL_image.h>
#include "Board.hpp"
#include <iostream>

using namespace std;

void Piece::draw(SDL_Surface *srcsurf, int bx, int by) {
  SDL_Rect rect;
  rect.x = toDispX(bx);
  rect.y = toDispY(by);
  rect.w = 80;
  rect.h = 80;
  SDL_BlitSurface(this->surface, NULL, srcsurf, &rect);
}

void Piece::setTransparent(SDL_Surface *surface) {
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0));
}

SDL_Surface *Piece::loadPiece(std::string path) {
  SDL_Surface *s = IMG_Load(path.c_str());
  setTransparent(s);
  return s;
}

void Piece::checkDirection(int modx, int mody,
                           std::vector<std::pair<int, int> > *v, int maxDepth) {
  for (int i = 1; i < maxDepth; i++) {

    int tox = x + modx * i;
    int toy = y + mody * i;

    int cm = canMove(tox, toy);

    if (cm == 0)
      break;

    v->push_back(std::make_pair(tox, toy));
    cout << "Adding pair " << tox << " " << toy << endl;
    if (cm == 1) {
      cout << "Different color, stopping" << endl;
      break;
    }
  }
}

// Returns 0 (can't move), 1 (move with capture), 2 (move)
int Piece::canMove(int tox, int toy) {
  if (tox > 7 || toy > 7 || tox < 0 || toy < 0)
    return 0;

  int toColor = board.colorAt(tox, toy);

  if (toColor == color)
    return 0;

  return (toColor == NONE) ? 2 : 1;
}

std::vector<std::pair<int, int> > Piece::allValidMoves() {
  // TODO implement additional checks
  return validMoves();
}
