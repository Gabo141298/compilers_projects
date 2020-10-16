#include <cctype>

#include "Rook.h"

Rook::Rook(char symbol, Board* board, Coordinates position)
    : Piece{symbol, board, position }
{
   
}

void Rook::calculatePossibleMoves()
{
    // Stores the directions in which the rook can move
    short xArray[] = { 1,0,-1,0 };
    short yArray[] = { 0,1,0,-1 };

    // Loops through the 4 possible directions.
    for ( int direction = 0; direction < 4; ++direction)
    {
        // The new x and y to check are added the direction
        short x = currentPosition.file + xArray[direction];
        short y = currentPosition.rank + yArray[direction];

        // While the cell is within boundaries and is free
        while( x>=0 && x<8 && y>=0 && y<8 && isFree(y, x))
        {
            // The move is valid, add it to possibleMoves
            possibleMoves.commutingMoves.push_back( Coordinates(y, x) );

            // Move the rook once more in the same direction
            x += xArray[direction]; y += yArray[direction];
        }

        // If the last cell wasn't free, but instead had an enemy
        if( isEnemy(y, x) )
            possibleMoves.capturingMoves.push_back( Coordinates(y, x) );
    }
}