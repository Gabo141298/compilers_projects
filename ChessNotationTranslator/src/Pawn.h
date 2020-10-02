#include "Piece.h"

#ifndef PAWN_H
#define PAWN_H

class Pawn : public Piece
{
  public:
  	Pawn(char symbol);

  	/*!
    * @brief Determine all of the moves in which the given pawn can move.
    * @details A pawn always has a max of 5 possible moves: moving once front,
    *          capturing to the left front, capturing two the right front, and
    *          two special moves, moving twice front if it is the pawn's first
    *          move, and promoting to another piece if it reaches the end of
    *          the board. This method checks if those moves are available for the
    *          given pawn, and if so, adds them to the corresponding vectors.
    * @return a MoveTypes struct with all the valid moves that the pawn can do.
    */
    MoveTypes getPossibleMoves();

    /// Checks if the pawn is still in its starting position (meaning this is its first move).
    bool isFirstMove();
};

#endif