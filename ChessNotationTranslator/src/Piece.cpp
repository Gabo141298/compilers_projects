#include "Piece.h"

#include <string>

std::ostream& operator<< (std::ostream &out, const Piece& piece)
{
    out << piece.symbol;
    return out;
}

bool Piece::isEnemy( short row, short file)
{
    // If it is out of boundaries
    if ( row < 0 || row > 7 || file < 0 || file > 7 || board[row][file] == nullptr)
        return false;

    // If the piece is black, check if the cell is upper case
    if ( std::islower(this->symbol) )
        return std::isupper(board[row][file]->getSymbol());

    // Return true if the piece in the cell is the opposite color to this
    return std::isupper(this->board[row][file]->getSymbol());
}

bool Piece::isFree( short row, short file)
{
    // If the cell is out of boundaries, it cannot be free
	if ( row < 0 || row > 7 || file < 0 || file > 7)
		return false;

    // Return true if the cell is not occupied, 
	return (this->board[row][file] == nullptr);
}