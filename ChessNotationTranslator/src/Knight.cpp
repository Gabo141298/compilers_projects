#include <cctype>

#include "Knight.h"

Knight::Knight(char symbol, Board* board, Coordinates position)
    : Piece{symbol, board, position }
{
    
}

MoveTypes Knight::getPossibleMoves()
{
	MoveTypes possibleMoves;

    short x[] = { -2,-1,1,2,2,1,-1,-2 };
    short y[] = { -1,-2,-2,-1,1,2,2,1 };

    for ( int direction = 0; direction < 8; ++direction)
    {
    	short newX = currentPosition.row + x[direction];
    	short newY = currentPosition.file + y[direction];

    	if ( isFree(newX, newY) ) 
            possibleMoves.commutingMoves.push_back( Coordinates(newX, newY) );
        else if ( isEnemy(newX, newY) )
            possibleMoves.capturingMoves.push_back( Coordinates(newX, newY) );
    }

    return possibleMoves;
}