#ifndef _PIECE_H_
#define _PIECE_H_

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <vector>

class Board;

const int WHITE = 0;
const int BLACK = 1;
const int NONE = 2;

// piece IDS
// TODO should use enum or a more OO approach
const int MAX_PID = 5;
const int PAWN_ID = 0;
const int KNIGHT_ID = 1;
const int BISHOP_ID = 2;
const int ROOK_ID = 3;
const int QUEEN_ID = 4;
const int KING_ID = 5;

typedef std::vector<std::pair<int, int> > MovesList;

class Piece {

public:
  Piece(Board &_board, int _pId, int _color, int _x, int _y,
        std::string blackImg, std::string whiteImg)
      : pid(_pId), x(_x), y(_y), color(_color), board(_board) {
    this->surface = color == BLACK ? loadPiece(blackImg) : loadPiece(whiteImg);
  }

  /** Returns a list of possible moves for this piece.
      A move is 'possible' if and only if it:
      1. corresponds to the movement pattern of the piece
      2. is within the bounds of the board
      3. it is not blocked by the placement of other pieces
      Additional validity checks should be performed in validMoves().
  */
  virtual MovesList possibleMoves() = 0;

  /** Returns a list of valid moves for this piece.
      A move is 'valid' if and only if it:
      1. is a possible move
      2. doesn't leave the current player in check
  */
  MovesList validMoves();

  /** Return a list of fields attacked by this piece. */
  virtual MovesList attackedFields() {
    return possibleMoves();
  }

  virtual ~Piece() {}

  void draw(SDL_Surface *srcsurf, int bx, int by);

  void move(int toX, int toY) {
    x = toX;
    y = toY;
  }

  inline int getColor() const { return color; }

  inline int getId() const { return pid; }

protected:
  inline int toDispX(int bx) const { return 80 * bx; }

  inline int toDispY(int by) const { return 80 * by; }

  void setTransparent(SDL_Surface *surface);
  SDL_Surface *loadPiece(std::string path);
  void checkDirection(int modx, int mody, MovesList *v,
                      int maxDepth = 8);
  int canMove(int tox, int toy);

  SDL_Surface *surface;
  int x, y;
  int color;
  Board &board;
  int pid;
};

#endif /* _PIECE_H_ */
