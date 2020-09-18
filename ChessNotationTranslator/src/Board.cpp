#include "Board.h"

Board::Board()
{
	// Initialize the board with the normal chess starting position
	for (int row = 0; row < this->boardSize; ++row)
	{
		// Sets the pieces for the first and last rows
		// Lower case means a black piece, upper case is a white piece
		if (row == 0 || row == 7)
		{
			squares[row][0] = (row == 0) ? new Piece('r') : new Piece('R');
			squares[row][1] = (row == 0) ? new Piece('n') : new Piece('N');
			squares[row][2] = (row == 0) ? new Piece('b') : new Piece('B');
			squares[row][3] = (row == 0) ? new Piece('q') : new Piece('Q');
			squares[row][4] = (row == 0) ? new Piece('k') : new Piece('K');
			squares[row][5] = (row == 0) ? new Piece('b') : new Piece('B');
			squares[row][6] = (row == 0) ? new Piece('n') : new Piece('N');
			squares[row][7] = (row == 0) ? new Piece('r') : new Piece('R');
		}
		else 
		{
			// All the other rows start with the same piece, either pawns or nothing
			for (int col = 1; col < 7; ++col)
			{
				// The second row is full of black pawns
				if (row == 1)
					squares[row][col] = new Piece('p');
				// The second to last row is full of white pawns
				else if (row == 6)
					squares[row][col] = new Piece('P');
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
 			out << board.squares[row][col] << ' ';
 		out << std::endl;
	}

	return out;
}