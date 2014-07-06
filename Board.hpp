#ifndef _BOARD_H_
#define _BOARD_H_

#include <SDL2/SDL.h>
#include <string>
#include <iostream>


// TODO make pieces an enum
const int EMPTY = 0;
const int PAWN = 1;

const int WHITE = 1;
const int BLACK = 2;

const int INVALID = 0;
const int SOURCE = 1;
const int VALID = 2;

using namespace std;

class Board {
public:
  Board() {
    initBoard();
    wPawnS = loadPiece("white_pawn.bmp");
    bPawnS = loadPiece("black_pawn.bmp");
  }

  ~Board() {
    // TODO free pawn surface
  }

  bool draw(SDL_Surface* surface) {
    SDL_FillRect(surface, NULL,
		 SDL_MapRGB(surface->format, 125, 125, 125));

    for (int j = 0; j <= 640; j+= 80) {
      int start = (j / 80) % 2 == 0 ? 0 : 80;
      for (int i = start; i <= 640; i+= 160) {
        SDL_Rect rect;
        rect.x = i;
        rect.y = j;
        rect.w = 80;
        rect.h = 80;
        SDL_FillRect(surface, &rect,
                     SDL_MapRGB(surface->format, 210, 210, 210));
      }
    }

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
	if (valid[i][j] != INVALID) {
	  SDL_Rect rect;
	  rect.x = toDispX(i);
	  rect.y = toDispY(j);
	  rect.w = 80;
	  rect.h = 80;
	  if (valid[i][j] == SOURCE)
	    SDL_FillRect(surface, &rect,
			 SDL_MapRGB(surface->format, 255, 255, 0));
	  else if (valid[i][j] == VALID)
	    SDL_FillRect(surface, &rect,
			 SDL_MapRGB(surface->format, 0, 255, 0));
	}

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++) {
	switch (board[i][j]) {
	  case PAWN:
	    if (color[i][j] == BLACK)
	      drawPiece(surface, i, j, bPawnS);
	    else
	      drawPiece(surface, i, j, wPawnS);
	    break;
	case EMPTY:
	  break;
	default:
	    std::cout << "Unkown piece type!" << std::endl;
	  }
      }

    return true;
  }

  // Returns true iff the select square is the source of a valid move
  bool select(int dx, int dy) {
    int bx = toBoardX(dx);
    int by = toBoardY(dy);

    if (!validateSelection(bx, by)) {
      return false;
    }

    updateValid(bx, by);

    return true;
  }

  // move piece from -> to coordinates (display coordinates)
  void movePiece(int fromX, int fromY, int  toX, int toY) {
    int fx = toBoardX(fromX);
    int fy = toBoardY(fromY);
    int tx = toBoardX(toX);
    int ty = toBoardY(toY);

    if (!validateMove(fx, fy, tx, ty))
      return;

    board[tx][ty] = board[fx][fy];
    board[fx][fy] = EMPTY;
    color[tx][ty] = color[fx][fy];
    color[fx][fy] = EMPTY;

    clearValid();
  }

private:

  void clearValid() {
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
	valid[i][j] = INVALID;
  }

  void updateValid(int bx, int by) {
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
	valid[bx][by] = INVALID;

    // TODO mark valid movement squares
    valid[bx][by] = SOURCE;
  }

  bool validateSelection(int bx, int by) {
    return board[bx][by] != EMPTY;
  }

  void printMove(int fx, int fy, int tx, int ty) {
    std::cout << "Moving piece from " << fx << " " << fy;
    std::cout << " to " << tx << " " << ty << std::endl;
    std::cout << board[fx][fy] << std::endl;
    std::cout << color[fx][fy] << std::endl;
  }

  bool validateMove(int fx, int fy, int tx, int ty) {
    // TODO add proper validation
    return fy != ty || fx != tx;
  }

  void drawPiece(SDL_Surface* surface, int bx, int by, SDL_Surface* piece) {
    SDL_Rect rect;
    rect.x = toDispX(bx);
    rect.y = toDispY(by);
    rect.w = 80;
    rect.h = 80;
    SDL_BlitSurface(piece, NULL, surface, &rect);
  }

  void setTransparent(SDL_Surface* surface) {
    SDL_SetColorKey(surface,
		    SDL_TRUE,
		    SDL_MapRGB(surface->format, 0, 255, 0) );
  }

  SDL_Surface* loadPiece(std::string path) {
    SDL_Surface* s = SDL_LoadBMP(path.c_str());
    setTransparent(s);
    return s;
  }

  int toDispX(int bx) {
    return 80 * bx;
  }

  int toDispY(int by) {
    return 80 * by;
  }

  int toBoardX(int dx) {
    return dx / 80;
  }

  int toBoardY(int dy) {
    return dy / 80;
  }

  void initBoard() {

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
	color[i][j] = EMPTY;
	board[i][j] = EMPTY;
	valid[i][j] = INVALID;
      }
    }

    for (int i = 0; i < 8; i++) {
      board[i][1] = PAWN;
      color[i][1] = WHITE;
      board[i][6] = PAWN;
      color[i][6] = BLACK;
    }
  }

  SDL_Surface* bPawnS;
  SDL_Surface* wPawnS;

  // board model
  int board[8][8];
  int color[8][8];

  // a list of valid moves for the current selection
  bool valid[8][8];
};


#endif /* _BOARD_H_ */
