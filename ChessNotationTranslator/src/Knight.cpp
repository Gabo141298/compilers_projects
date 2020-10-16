#include <cctype>

#include "Knight.h"

Knight::Knight(char symbol, Board* board, Coordinates position)
    : Piece{symbol, board, position }
{
    
}

void Knight::calculatePossibleMoves()
{
    short x[] = { -2,-1,1,2,2,1,-1,-2 };
    short y[] = { -1,-2,-2,-1,1,2,2,1 };

    for ( int direction = 0; direction < 8; ++direction)
    {
    	short newX = currentPosition.file + x[direction];
    	short newY = currentPosition.rank + y[direction];

    	if ( isFree(newY, newX) ) 
            possibleMoves.commutingMoves.push_back( Coordinates(newY, newX) );
        else if ( isEnemy(newY, newX) )
            possibleMoves.capturingMoves.push_back( Coordinates(newY, newX) );
    }
}