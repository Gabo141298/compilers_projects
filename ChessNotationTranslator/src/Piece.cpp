#include "Board.h"
#include "Piece.h"

#include <string>

std::ostream& operator<< (std::ostream &out, const Piece& piece)
{
    out << piece.symbol;
    return out;
}

bool Piece::isEnemy( short file, short rank)
{
    // If it is out of boundaries
    if ( file < 0 || file > 7 || rank < 0 || rank > 7 || board->getSquare(file,rank) == nullptr)
        return false;

    // If the piece is black, check if the cell is upper case
    if ( std::islower(this->symbol) )
        return std::isupper(board->getSquare(file,rank)->getSymbol());

    // Return true if the piece in the cell is the opposite color to this
    return std::isupper(this->board->getSquare(file,rank)->getSymbol());
}

bool Piece::isFree( short file, short rank)
{
    // If the cell is out of boundaries, it cannot be free
	if ( file < 0 || file > 7 || rank < 0 || rank > 7)
		return false;

    // Return true if the cell is not occupied, 
	return (this->board->getSquare(file,rank)== nullptr);
}
