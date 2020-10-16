#include <cctype>

#include "King.h"

King::King(char symbol, Board* board, Coordinates position)
    : Piece{symbol, board, position }
{
}

// Method to get the possible moves for the king
// The king can move vertically, horizontally and
// diagonally in any direction, but only one square
// at a time
void King::calculatePossibleMoves()
{
    // The directions in which the king may go
    short x[] = { 1,1,0,-1,-1,-1,0,1 };
    short y[] = { 0,1,1,1,0,-1,-1,-1 };

    // Goes through the 8 possible directions
    for ( int direction = 0; direction < 8; ++direction)
    {
    	short newX = currentPosition.file + x[direction];
    	short newY = currentPosition.rank + y[direction];

        // If the cell is free, add the move to commutingMoves
    	if ( isFree(newY, newX) ) 
            possibleMoves.commutingMoves.push_back( Coordinates(newY, newX) );

        // If the cell was occupied by an enemy, add the move to capturingMoves
        else if ( isEnemy(newY, newX) )
            possibleMoves.capturingMoves.push_back( Coordinates(newY, newX) );
    }

    short rank = currentPosition.rank; 
    // For castling
    if ( !hasMoved ) 
    {
        // Short castle
        if ( isFree(rank, 5) && isFree(rank, 6))
            possibleMoves.castle.push_back( Coordinates(currentPosition.rank, 5));

        // Long castle
        if ( isFree(rank, 1) && isFree(rank, 2) && isFree(rank, 3))
            possibleMoves.castle.push_back( Coordinates(currentPosition.rank, 3));
    }
}