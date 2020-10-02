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

bool Board::isRightTurn(Piece* selectedPiece)
{
    if ( islower(selectedPiece->getSymbol()) )
        return ( manager.getTurn() == 1 );

    return ( manager.getTurn() == 0 );
}

void Board::savePieceIfPossible(Piece* selectedPiece, int rowPos, int colPos)
{
    // If the cell has a Piece, it keeps the pointer, else, it will have a nullptr.
    selectedPiece = squares[rowPos][colPos];
    if(selectedPiece)
    {
        // Checks if the piece selected corresponds with the current turn
        if ( isRightTurn(selectedPiece) )
        {
            validMoves = selectedPiece->getPossibleMoves();
            std::cerr << validMoves.commutingMoves.size() << '-' << validMoves.capturingMoves.size() << std::endl;

            // If there are no possible moves, then the piece shouldn't be selected.
            if(validMoves.commutingMoves.size() == 0 && validMoves.capturingMoves.size() == 0)
                selectedPiece = nullptr;
        }
        // If the turn wasn't correct, the piece could not be selected.
        else
        {
            selectedPiece = nullptr;
        }
    }
}

void Board::movePieceIfPossible(Piece* selectedPiece, int rowPos, int colPos)
{
    bool validMove = false;

    // Checks if the move made by the player was any of the commuting moves
    for(unsigned int index = 0; index < validMoves.commutingMoves.size() && !validMove; ++index)
    {
        if(colPos == validMoves.commutingMoves[index].file && rowPos == validMoves.commutingMoves[index].row)
        {
            movePiece(selectedPiece, rowPos, colPos);
            validMove = true;
        }
    }

    // Checks if the move made was a capture to another piece
    for(unsigned int index = 0; index < validMoves.capturingMoves.size() && !validMove; ++index)
    {
        if(colPos == validMoves.capturingMoves[index].file && rowPos == validMoves.capturingMoves[index].row)
        {
            delete squares[rowPos][colPos];
            squares[rowPos][colPos] = nullptr;

            // Makes the move from the last piece to the chosen cell
            movePiece(selectedPiece, rowPos, colPos);
            validMove = true;
        }
    }

    // If the moved chosen was a valid one
    if(validMove)
    {
        // The en passant rule only applies for one turn. So, it has to be cancelled after every move.
        resetOpponentEnPassants();

        // Change turns
        manager.changeTurn();
    }

    manager.setGameState();
}

void Board::resetOpponentEnPassants()
{
	char opponentSymbol = (manager.getTurn()) ? 'P' : 'p';

	// Initialize the board with the normal chess starting position
	for (int row = 0; row < this->boardSize; ++row)
	{
		// All the other rows start with the same piece, either pawns or nothing
		for (int col = 0; col < this->boardSize; ++col)
		{
			if(squares[row][col]->getSymbol() == opponentSymbol)
			{
				// set the justMovedTwiced to false
				//squares[row][col]->getSquare->resetJustMovedTwice();
				;
			}			
		}
	}

}

void Board::movePiece(Piece* selectedPiece, int rowPos, int colPos)
{
    // If the piece is a pawn, and it is in the last rank, a promotion move ocurred
    if ( ( selectedPiece->getSymbol() == 'P' || selectedPiece->getSymbol() == 'p') && ( rowPos == 7 || rowPos == 0 ) )
    {
        // Delete the pawn from the board
        delete squares[selectedPiece->getPosition().row][selectedPiece->getPosition().file];

        // The new piece will be either a black or a white queen
        char newSymbol = (rowPos) ? 'q' : 'Q';

        // Creates the piece and assign it a Queen image
        squares[rowPos][colPos] = selectedPiece = new Queen(newSymbol, this, selectedPiece->getPosition());
    }

    // Make the piece move and add it to the board;
    squares[rowPos][colPos] = selectedPiece;
    squares[rowPos][colPos]->setPosition(Coordinates(rowPos, colPos));
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