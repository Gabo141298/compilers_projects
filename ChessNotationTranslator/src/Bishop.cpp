#include "Bishop.h"

Bishop::Bishop(char symbol)
    : Piece{symbol}
{

}

MoveTypes Bishop::getPossibleMoves()
{
	// Store all the possible valid moves for the bishop
    MoveTypes possibleMoves;

    // Stores the directions in which the bishop can move
    short xArray[] = { -1,1,1,-1 };
    short yArray[] = { -1,-1,1,1 };

    // Loops through the 4 possible directions.
    for ( int direction = 0; direction < 4; ++direction)
    {
    	// The new x and y to check are added the direction
    	short x = currentPosition.row + xArray[direction];
    	short y = currentPosition.file + yArray[direction];

    	// While the cell is within boundaries and is free
    	while( x>=0 && x<8 && y>=0 && y<8 && isFree(x, y))
    	{
    		// The move is valid, add it to possibleMoves
            possibleMoves.commutingMoves.push_back( Coordinates(x, y) );

    		// Move the bishop once more in the same direction
    		x += xArray[direction]; y += yArray[direction];
    	}

    	// If the last cell wasn't free, but instead had an enemy
    	if( isEnemy(x,y) )
            possibleMoves.capturingMoves.push_back( Coordinates(x, y) );
    }

    // Return all the possible valid moves the bishop could make
    return possibleMoves;
}