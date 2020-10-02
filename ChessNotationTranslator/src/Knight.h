#include "Piece.h"

#ifndef KNIGHT_H
#define KNIGHT_H

class Knight : public Piece
{
  public:
    Knight(char symbol, Board* board, Coordinates position);

    MoveTypes getPossibleMoves();
};


#endif // KNIGHT_H