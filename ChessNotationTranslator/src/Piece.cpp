#include "Piece.h"

#include <string>
std::ostream& operator<< (std::ostream &out, const Piece& piece)
{
    out << piece.symbol;
    return out;
}

