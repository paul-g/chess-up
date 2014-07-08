#include "Board.hpp"

Board::Board(SDL_Surface* _surface) :
  surface(_surface), init(true) {
  toMove = WHITE;
  initBoard();
}

Board::~Board() {
  std::cout << "Board::~Board" << std::endl;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      if (board[i][j] != nullptr)
        delete board[i][j];
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
          SDL_FillRect(surface, &rect,
                       SDL_MapRGB(surface->format, 0, 255, 0));
        }
      }

      // draw piece
      if (board[i][j] != nullptr) {
        // reset square and draw piece
        board[i][j]->draw(surface, i, j);
        continue;
      }
    }

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      changed[i][j] = false;

  if (updated)
    std::cout << "Updated cells " << updateCount << std::endl;

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
void Board::movePiece(int fromX, int fromY, int  toX, int toY) {
  int fx = toBoardX(fromX);
  int fy = toBoardY(fromY);
  int tx = toBoardX(toX);
  int ty = toBoardY(toY);

  if (!validateMove(fx, fy, tx, ty)) {
    cout << "Invalid move (" << fx << " " << fy;
    cout << ") --> ("  << tx << " " << ty << ")" << endl;
    clearValid();
    return;
  }

  Piece *p = board[fx][fy];

  if (board[tx][ty] && board[tx][ty]->getColor() != toMove) {
    capture(board[tx][ty]);
  }

  board[tx][ty] = p;
  board[fx][fy] = nullptr;
  p->move(tx, ty);

  clearValid();

  toMove = (toMove == WHITE) ? BLACK : WHITE;
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

bool Board::validateSelection(int bx, int by) {
  Piece* p = board[bx][by];
  if (!p)
    return false;
  return p->getColor() == toMove;
}

void Board::printMove(int fx, int fy, int tx, int ty) {
  std::cout << "Moving piece from " << fx << " " << fy;
  std::cout << " to " << tx << " " << ty << std::endl;
  std::cout << board[fx][fy] << std::endl;
}

bool Board::validateMove(int fx, int fy, int tx, int ty) {
  return valid[tx][ty] == VALID;
}

void Board::initBoard() {
  std::cout << "Init board" << std::endl;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = nullptr;
      valid[i][j] = INVALID;
      changed[i][j] = true;
    }
  }

  for (int i = 0; i < 8; i++) {
    board[i][1] = new Pawn(*this, WHITE, i, 1);
    board[i][6] = new Pawn(*this, BLACK, i, 6);
  }
}

int Board::colorAt(int bx, int by) {
  if (bx < 0 || bx > 7 ||
      by < 0 || by > 7 ||
      board[bx][by] == nullptr)
    return NONE;

  return board[bx][by]->getColor();
}

void Board::drawSquare(int i, int j) {
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

void Board::capture(Piece* p) {
  int pos = p->getColor() == WHITE ? 6 : 1;
  p->draw(surface, 8, pos);
}
