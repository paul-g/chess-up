#ifndef _BOARD_H_
#define _BOARD_H_

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Piece.hpp"
#include "Pawn.hpp"

// TODO make pieces an enum
const int EMPTY = 0;
const int PAWN = 1;

const int INVALID = 0;
const int SOURCE = 1;
const int VALID = 2;

using namespace std;

class Board {
public:
  Board();
  ~Board();

  bool draw(SDL_Surface* surface);

  // Returns true iff the select square is the source of a valid move
  bool select(int dx, int dy);

  // move piece from -> to coordinates (display coordinates)
  void movePiece(int fromX, int fromY, int  toX, int toY);

  int colorAt(int bx, int by);

private:
  void clearValid();
  void updateValid(int bx, int by);
  bool validateSelection(int bx, int by);
  void printMove(int fx, int fy, int tx, int ty);
  bool validateMove(int fx, int fy, int tx, int ty);
  void initBoard();
  void drawSquare(int i, int j, SDL_Surface* surface);


  inline int toDispX(int bx) const {
    return 80 * bx;
  }

  inline int toDispY(int by) const {
    return 80 * by;
  }

  inline int toBoardX(int dx) const {
    return dx / 80;
  }

  inline int toBoardY(int dy) const {
    return dy / 80;
  }

  // board model
  Piece* board[8][8];
  bool changed[8][8];

  // a list of valid moves for the current selection
  int valid[8][8];

  bool init;
  int toMove;
};


#endif /* _BOARD_H_ */
