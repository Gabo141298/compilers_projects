#include "Board.h"
#include "Piece.h"

#include <string>

std::ostream& operator<< (std::ostream &out, const Piece& piece)
{
    out << piece.symbol;
    return out;
}

bool Piece::isEnemy( short rank, short file)
{
    std::cout <<  "Search enemy" << rank << file <<std::endl;
    // If it is out of boundaries
    if ( file < 0 || file > 7 || rank < 0 || rank > 7 || board->getSquare(rank, file) == nullptr)
        return false;

    // If the piece is black, check if the cell is upper case
    if ( std::islower(this->symbol) )
    {
        std::cout << board->getSquare(rank, file)->getSymbol();
        return std::isupper(board->getSquare(rank, file)->getSymbol());
    }

    // Return true if the piece in the cell is the opposite color to this
    return std::isupper(this->board->getSquare(rank, file)->getSymbol());
}

bool Piece::isFree( short rank, short file)
{
    // If the cell is out of boundaries, it cannot be free
	if ( file < 0 || file > 7 || rank < 0 || rank > 7)
		return false;

    // Return true if the cell is not occupied, 
	return (this->board->getSquare(rank, file)== nullptr);
}
