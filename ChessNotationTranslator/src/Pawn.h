#include "Piece.h"

#ifndef PAWN_H
#define PAWN_H

class Pawn : public Piece
{
  private: 
    /// Stores if the pawn just made its first move by advancing two squares. Useful for en passant.
    bool justMovedTwice = false;
  private:
    /// Checks if it can take a pawn next to it en passant
    bool canEnPassant(short row, short file);

  public:
  	Pawn(char symbol, Board* board, Coordinates position);

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
    void calculatePossibleMoves();

    /// Checks if the pawn is still in its starting position (meaning this is its first move).
    bool isFirstMove();

    /// Returns the value of the justMovedTwice 
    inline bool getJustMovedTwice() { return this->justMovedTwice; }

    inline void resetJustMovedTwice() { this->justMovedTwice = false; }
};

#endif