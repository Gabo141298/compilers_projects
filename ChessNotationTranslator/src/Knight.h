#include "Piece.h"

#ifndef KNIGHT_H
#define KNIGHT_H

class Knight : public Piece
{
  public:
    Knight(char symbol, Board* board, Coordinates position);

    /*!
    * @details Determine all the possible cells to which the
    *	     knight can move. It checks cells in L form, that
    *		 is: two squares in a file and one square in the 
    *		 rank, or two squares in a rank and one square in
    *		 a file away from where it currently is.
    */
    void calculatePossibleMoves();
};


#endif // KNIGHT_H