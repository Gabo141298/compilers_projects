#include <cctype>

#include "Board.h"
#include "Pawn.h"

Pawn::Pawn(char symbol, Board* board, Coordinates position)
    : Piece{symbol, board, position }
{
}

void Pawn::calculatePossibleMoves()
{
    // If the pawn is black, it moves up, if it is white, it moves down.
    int direction = (this->symbol == 'P') ? -1 : 1;

    // If this is the pawns first move, it can move twice front (if the cell is free)
    if ( isFirstMove() && isFree(currentPosition.rank+(2*direction), currentPosition.file))
        possibleMoves.commutingMoves.push_back( Coordinates(currentPosition.rank+(2*direction), currentPosition.file) );\

    // If the cell in front of the pawn is empty, it can move there
    if ( isFree(currentPosition.rank+direction, currentPosition.file))
        possibleMoves.commutingMoves.push_back( Coordinates(currentPosition.rank+direction, currentPosition.file) );
    
    // If there is an enemy to the front diagonals, the pawn can capture it
    if ( isEnemy(currentPosition.rank+direction, currentPosition.file+1) )
        possibleMoves.capturingMoves.push_back( Coordinates(currentPosition.rank+direction, currentPosition.file+1) );
    if ( isEnemy(currentPosition.rank+direction, currentPosition.file-1) )
        possibleMoves.capturingMoves.push_back( Coordinates(currentPosition.rank+direction, currentPosition.file-1) );

    // En passant. Take the enemy next to you, by moving diagonally. It's a weird move, look it up.
    if ( canEnPassant(currentPosition.rank, currentPosition.file+1))
        possibleMoves.capturingMoves.push_back( Coordinates(currentPosition.rank+direction, currentPosition.file+1) );
    if ( canEnPassant(currentPosition.rank, currentPosition.file-1))
        possibleMoves.capturingMoves.push_back( Coordinates(currentPosition.rank+direction, currentPosition.file-1) );
}

bool Pawn::canEnPassant(short rank, short file)
{
    Piece* pieceToCheck = this->board->getSquare(rank,file);

    // First we have to check that the square has a piece, and that piece is an opponent pawn
    if ( pieceToCheck && this->isEnemy(rank,file) && (pieceToCheck->getSymbol() == 'P' || pieceToCheck->getSymbol() == 'p') )
        // Now we check if the pawn just moved twice: the requisite for en passant captures
        //if ( pieceToCheck->getJustMovedTwice()) 
            return true;

    return false;
}

bool Pawn::isFirstMove()
{
    // If the white pawn is in its starting position
    if ( this->symbol == 'P' && currentPosition.rank == 6)
        return true;

    // If black pawn is in its starting position
    if ( this->symbol == 'p' && currentPosition.rank == 1)
        return true;

    return false;
}