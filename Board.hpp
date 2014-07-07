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
  Board() {
    init = true;
    initBoard();
  }

  ~Board() {
    std::cout << "Board::~Board" << std::endl;
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
        if (board[i][j] != nullptr)
          delete board[i][j];
  }

  bool draw(SDL_Surface* surface) {
    bool updated = false;
    int updateCount = 0;

    if (init) {
      for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
          SDL_Rect rect;
          rect.x = toDispX(i);
          rect.y = toDispY(j);
          rect.w = 80;
          rect.h = 80;
          if ((i + j) % 2 == 0)
            SDL_FillRect(surface, &rect,
                         SDL_MapRGB(surface->format, 210, 210, 210));
          else
            SDL_FillRect(surface, &rect,
                         SDL_MapRGB(surface->format, 125, 125, 125));
        }
      init = false;
      return true;
    }

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++) {

        if (!changed[i][j])
          continue;
        updated = true;
        updateCount++;


        SDL_Rect rect;
        rect.x = toDispX(i);
        rect.y = toDispY(j);
        rect.w = 80;
        rect.h = 80;

        if (valid[i][j] != INVALID) {
          if (valid[i][j] == SOURCE)
            SDL_FillRect(surface, &rect,
                         SDL_MapRGB(surface->format, 255, 255, 0));

          if (valid[i][j] == VALID) {
            SDL_FillRect(surface, &rect,
                         SDL_MapRGB(surface->format, 0, 255, 0));
          }

          if (board[i][j] != nullptr)
            board[i][j]->draw(surface, i, j);

          continue;
        }

        if (board[i][j] != nullptr) {
          // reset square and draw piece
          if ((i + j) % 2 == 0)
            SDL_FillRect(surface, &rect,
                         SDL_MapRGB(surface->format, 210, 210, 210));
          else
            SDL_FillRect(surface, &rect,
                         SDL_MapRGB(surface->format, 125, 125, 125));

          board[i][j]->draw(surface, i, j);
          continue;
        }

        if ((i + j) % 2 == 0)
          SDL_FillRect(surface, &rect,
                       SDL_MapRGB(surface->format, 210, 210, 210));
        else
          SDL_FillRect(surface, &rect,
                       SDL_MapRGB(surface->format, 125, 125, 125));
      }

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
        changed[i][j] = false;

    if (updated)
      std::cout << "Updated cells " << updateCount << std::endl;

    init = false;
    return true;
  }

  bool update(SDL_Surface* surface) {

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
    board[fx][fy] = nullptr;

    clearValid();
  }

private:

  void clearValid() {
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++) {
        if (valid[i][j] != INVALID)
          changed[i][j] = true;
        valid[i][j] = INVALID;
      }
  }

  void updateValid(int bx, int by) {
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
        valid[bx][by] = INVALID;

    valid[bx][by] = SOURCE;
    changed[bx][by] = true;

    // TODO mark valid movement squares
    Piece* p = board[bx][by];
    auto moves = p->validMoves();
    for  (auto m : moves) {
      std::cout << "Moves" << std::endl;
      int x = m.first;
      int y = m.second;
      valid[x][y] = VALID;
      changed[x][y] = true;
    }

  }

  bool validateSelection(int bx, int by) {
    return board[bx][by] != nullptr;
  }

  void printMove(int fx, int fy, int tx, int ty) {
    std::cout << "Moving piece from " << fx << " " << fy;
    std::cout << " to " << tx << " " << ty << std::endl;
    std::cout << board[fx][fy] << std::endl;
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
    std::cout << "Init board" << std::endl;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        board[i][j] = nullptr;
        valid[i][j] = INVALID;
        changed[i][j] = true;
      }
    }

    for (int i = 0; i < 8; i++) {
      board[i][1] = new Pawn(WHITE, i, 1);
      board[i][6] = new Pawn(BLACK, i, 6);
    }
  }

  // board model
  Piece* board[8][8];
  bool changed[8][8];

  // a list of valid moves for the current selection
  int valid[8][8];

  bool init;
};


#endif /* _BOARD_H_ */
