#include "Piece.h"

#ifndef QUEEN_H
#define QUEEN_H

class Queen : public Piece
{
  public:
  	Queen(char symbol);

  	/*!
    * @details Determine all the possible cells to which a given
    *	     queen can move. It checks cells vertically, horizontally
    		 and diagonally
    * @return an std::vector with all the moves that the queen can
    *		  do moving to left, right, up, down or in diags
    */
    MoveTypes getPossibleMoves() override;
};

#endif