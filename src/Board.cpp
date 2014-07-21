#include "Board.hpp"

#include "SDL2/SDL_ttf.h"
#include <sstream>

#include "Bishop.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "Knight.hpp"
#include "King.hpp"

using namespace std;

Board::Board(SDL_Surface *_surface) : surface(_surface), init(true) {
  toMove = WHITE;
  initBoard();
}

Board::~Board() {
  cout << "Board::~Board" << endl;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      if (board[i][j])
        delete board[i][j];

  for (auto p : captured)
    delete p;

  TTF_CloseFont(font);
  TTF_Quit();
}

bool Board::draw() {
  bool updated = false;
  int updateCount = 0;

  if (init) {
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
        drawSquare(i, j);
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
      rect.x = toDispX(i) + 20;
      rect.y = toDispY(j) + 20;
      rect.w = 40;
      rect.h = 40;

      // redraw square
      drawSquare(i, j);

      // apply highlight
      if (valid[i][j] != INVALID) {
        if (valid[i][j] == SOURCE)
          SDL_FillRect(surface, &rect,
                       SDL_MapRGB(surface->format, 255, 255, 0));

        if (valid[i][j] == VALID) {
          SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0, 255, 0));
        }
      }

      // draw piece
      if (board[i][j]) {
        // reset square and draw piece
        board[i][j]->draw(surface, i, j);
        continue;
      }
    }

  drawCaptured();

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      changed[i][j] = false;

  if (updated)
    cout << "Updated cells " << updateCount << endl;

  init = false;
  return true;
}

// Returns true iff the select square is the source of a valid move
bool Board::select(int dx, int dy) {
  int bx = toBoardX(dx);
  int by = toBoardY(dy);

  if (!validateSelection(bx, by)) {
    return false;
  }

  updateValid(bx, by);

  return true;
}

// move piece from -> to coordinates (display coordinates)
bool Board::movePiece(int fromX, int fromY, int toX, int toY) {
  int fx = toBoardX(fromX);
  int fy = toBoardY(fromY);
  int tx = toBoardX(toX);
  int ty = toBoardY(toY);

  if (!validateMove(fx, fy, tx, ty)) {
    cout << "Invalid move (" << fx << " " << fy;
    cout << ") --> (" << tx << " " << ty << ")" << endl;
    clearValid();
    return false;
  }

  Piece *p = board[fx][fy];

  if (board[tx][ty] && board[tx][ty]->getColor() != toMove) {
    capture(board[tx][ty]);
  }

  board[tx][ty] = p;
  board[fx][fy] = nullptr;
  p->move(tx, ty);

  clearValid();

  return true;
}

void Board::clearValid() {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
      if (valid[i][j] != INVALID)
        changed[i][j] = true;
      valid[i][j] = INVALID;
    }
}

void Board::updateValid(int bx, int by) {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      valid[bx][by] = INVALID;

  valid[bx][by] = SOURCE;
  changed[bx][by] = true;

  // TODO mark valid movement squares
  Piece *p = board[bx][by];
  auto moves = p->validMoves();
  for (auto m : moves) {
    cout << "Moves" << endl;
    int x = m.first;
    int y = m.second;
    valid[x][y] = VALID;
    changed[x][y] = true;
  }
}

bool Board::validateSelection(int bx, int by) {
  Piece *p = board[bx][by];
  if (!p)
    return false;
  return p->getColor() == toMove;
}

void Board::printMove(int fx, int fy, int tx, int ty) {
  cout << "Moving piece from " << fx << " " << fy;
  cout << " to " << tx << " " << ty << endl;
  cout << board[fx][fy] << endl;
}

bool Board::validateMove(int fx, int fy, int tx, int ty) {
  // TODO: ensure the move doesn't leave the current player in check
  return valid[tx][ty] == VALID;
}

void Board::initBoard() {
  cout << "Init board" << endl;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = nullptr;
      valid[i][j] = INVALID;
      changed[i][j] = true;
    }
  }

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < MAX_PID; j++)
      capturedCount[i][j] = make_pair(nullptr, 0);

  for (int i = 0; i < 8; i++) {
    board[i][1] = new Pawn(*this, WHITE, i, 1);
    board[i][6] = new Pawn(*this, BLACK, i, 6);
  }

  board[2][0] = new Bishop(*this, WHITE, 2, 0);
  board[5][0] = new Bishop(*this, WHITE, 5, 0);
  board[2][7] = new Bishop(*this, BLACK, 2, 7);
  board[5][7] = new Bishop(*this, BLACK, 5, 7);

  board[1][0] = new Knight(*this, WHITE, 1, 0);
  board[6][0] = new Knight(*this, WHITE, 6, 0);
  board[1][7] = new Knight(*this, BLACK, 1, 7);
  board[6][7] = new Knight(*this, BLACK, 6, 7);

  board[0][0] = new Rook(*this, WHITE, 0, 0);
  board[7][0] = new Rook(*this, WHITE, 7, 0);

  board[0][7] = new Rook(*this, BLACK, 0, 7);
  board[7][7] = new Rook(*this, BLACK, 7, 7);

  board[4][0] = new Queen(*this, WHITE, 4, 0);
  board[4][7] = new Queen(*this, BLACK, 4, 7);

  board[3][0] = new King(*this, WHITE, 3, 0);
  board[3][7] = new King(*this, BLACK, 3, 7);

  // init fonts
  if (TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
  }

  font = TTF_OpenFont("fonts/FreeSerif.ttf", 20);
  if (font == NULL) {
    cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
    TTF_Quit();
    SDL_Quit();
    exit(1);
  }

  text_color = { 255, 255, 255 };
}

int Board::colorAt(int bx, int by) {
  if (bx < 0 || bx > 7 || by < 0 || by > 7 || !board[bx][by])
    return NONE;

  return board[bx][by]->getColor();
}

void Board::drawSquare(int i, int j) {
  SDL_Rect rect;
  rect.x = toDispX(i);
  rect.y = toDispY(j);
  rect.w = 80;
  rect.h = 80;
  int c = (i + j) % 2 == 0 ? 210 : 125;
  SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, c, c, c));
}

void Board::capture(Piece *p) {
  captured.push_back(p);
  int c = p->getColor();
  int pid = p->getId();
  pair<Piece *, int> pp = capturedCount[c][pid];
  capturedCount[c][pid] = make_pair(p, pp.second + 1);
}

void Board::drawCaptured() {
  // TOOD should only draw the changed pieces
  for (int i = 0; i < 2; i++) {
    int pos = (i == 0) ? 6 : 1;
    for (int pId = 0; pId < MAX_PID; pId++) {
      int count = capturedCount[i][pId].second;
      if (count == 0)
        continue;
      stringstream ss;
      ss << "x ";
      ss << count;
      int x = 8 + pId % 3;
      int y = pos - pId / 3;
      capturedCount[i][pId].first->draw(surface, x, y);

      SDL_Rect rect;
      rect.x = toDispX(x) + 20;
      // TODO adjust y position of text
      rect.y = toDispY(y) + 80;
      rect.w = 40;
      rect.h = 20;

      SDL_Surface *text =
          TTF_RenderText_Solid(font, ss.str().c_str(), text_color);
      SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 125, 125, 125));

      SDL_BlitSurface(text, NULL, surface, &rect);
    }
  }
}

bool Board::currentPlayerInCheck() { return inCheck(toMove); }

bool Board::opponentInCheck() { return inCheck(1 - toMove); }

bool Board::inCheck(int color) {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
      if (!board[i][j])
        continue;
      auto moves = board[i][j]->validMoves();
      for (auto p : moves) {
        Piece *piece = board[p.first][p.second];
        if (!piece)
          continue;
        if (piece->getColor() == color && piece->getId() == KING_ID) {
          return true;
        }
      }
    }
  return false;
}

void Board::updateToMove() { toMove = (toMove == WHITE) ? BLACK : WHITE; }
