#include "Board.h"

#include "Bishop.h"
#include "Knight.h"
#include "King.h"

Piece* Board::factory(char symbol)
{
	switch(symbol)
	{
		case 'B':
		case 'b':
			return new Bishop(symbol);
		case 'N':
		case 'n':
			return new Knight(symbol);
		case 'K':
		case 'k':
			return new King(symbol);
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
			squares[row][0] = (row == 0) ? factory('r') : factory('R');
			squares[row][1] = (row == 0) ? factory('n') : factory('N');
			squares[row][2] = (row == 0) ? factory('b') : factory('B');
			squares[row][3] = (row == 0) ? factory('q') : factory('Q');
			squares[row][4] = (row == 0) ? factory('k') : factory('K');
			squares[row][5] = (row == 0) ? factory('b') : factory('B');
			squares[row][6] = (row == 0) ? factory('n') : factory('N');
			squares[row][7] = (row == 0) ? factory('r') : factory('R');
		}
		else 
		{
			// All the other rows start with the same piece, either pawns or nothing
			for (int col = 0; col < this->boardSize; ++col)
			{
				// The second row is full of black pawns
				if (row == 1)
				{
					squares[row][col] = factory('p');
					// std::cout << "Estoy haciendo peones" << row << col;
				}	

				// The second to last row is full of white pawns
				else if (row == 6)
					squares[row][col] = factory('P');
				// All the other rows have nothing
				else
					squares[row][col] = nullptr;
			}
		}
	}
	// for(int row = 0; row < boardSize; ++row)
	// {
 // 		for(int col = 0; col < boardSize; ++col)
 // 			std::cout << squares[row][col]->symbol << ' ';
 // 		std::cout << std::endl;
	// }
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