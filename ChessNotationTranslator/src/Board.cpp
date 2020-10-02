#include "Board.h"

#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

Piece* Board::factory(char symbol, int row, int col)
{
	Coordinates position(row,col);
	switch(symbol)
	{
		case 'B':
		case 'b':
			return new Bishop(symbol, this, position);
		case 'K':
		case 'k':
			return new King(symbol, this, position);
		case 'N':
		case 'n':
			return new Knight(symbol, this, position);
		case 'P':
		case 'p':
			return new Pawn(symbol, this, position);
		case 'Q':
		case 'q':
			return new Queen(symbol, this, position);
		case 'R':
		case 'r':
			return new Rook(symbol, this, position);
		default: 
			return nullptr;
	}
}

Board::Board()
{
	// Initialize the board with the normal chess starting position
	for (int row = 0; row < this->boardSize; ++row)
	{
		// Sets the pieces for the first and last rows
		// Lower case means a black piece, upper case is a white piece
		if (row == 0 || row == 7)
		{
			squares[row][0] = factory( (row == 0) ? 'r' : 'R', row, 0); 
			squares[row][1] = factory( (row == 0) ? 'n' : 'N', row, 1); 
			squares[row][2] = factory( (row == 0) ? 'b' : 'B', row, 2); 
			squares[row][3] = factory( (row == 0) ? 'q' : 'Q', row, 3); 
			squares[row][4] = factory( (row == 0) ? 'k' : 'K', row, 4); 
			squares[row][5] = factory( (row == 0) ? 'b' : 'B', row, 5); 
			squares[row][6] = factory( (row == 0) ? 'n' : 'N', row, 6); 
			squares[row][7] = factory( (row == 0) ? 'r' : 'R', row, 7); 
		}
		else 
		{
			// All the other rows start with the same piece, either pawns or nothing
			for (int col = 0; col < this->boardSize; ++col)
			{
				Coordinates position(row, col);

				// The second row is full of black pawns
				if (row == 1)
				{
					squares[row][col] = factory('p', row, col);
				}	

				// The second to last row is full of white pawns
				else if (row == 6)
					squares[row][col] = factory('P', row, col);
				// All the other rows have nothing
				else
					squares[row][col] = nullptr;
			}
		}
	}
}

Board::~Board()
{
	for (int row = 0; row < boardSize; ++row)
	{
		for (int col = 0; col < boardSize; ++col)
		{
			delete this->squares[row][col];
		}
	}
}

std::ostream& operator<<(std::ostream &out, const Board &board)
{
	for(int row = 0; row < board.boardSize; ++row)
	{
 		for(int col = 0; col < board.boardSize; ++col)
 		{
 			if(board.squares[row][col] == nullptr)
 				out << '_';
 			else
 				out	 << *board.squares[row][col];
 			out << ' ';
 		}
 		out << std::endl;
	}

	return out;
}