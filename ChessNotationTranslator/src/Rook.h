#include "Piece.h"

#ifndef ROOK_H
#define ROOK_H

class Rook : public Piece
{
  private: 
  	bool hasMoved = false;

  public:
  	Rook(char symbol, Board* board, Coordinates position);

  	/*!
    * @details Determine all the possible cells to which a given
    *	     rook can move. It checks cells vertically and horizontally
    * @return an std::vector with all the moves that the rook can
    *		  do moving to left, right, up or down
    */
    void calculatePossibleMoves() override;

    inline bool getHasMoved() { return hasMoved; }
};

#endif