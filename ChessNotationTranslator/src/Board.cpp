#include "Board.h"

#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

#include <cctype>

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
		if (row == 0)
		{
			squares[0][0] = factory( 'r', row, 0); 
			squares[0][1] = factory( 'n', row, 1); 
			squares[0][2] = factory( 'b', row, 2); 
			squares[0][3] = factory( 'q', row, 3); 
			squares[0][4] = factory( 'k', row, 4); 
			squares[0][5] = factory( 'b', row, 5); 
			squares[0][6] = factory( 'n', row, 6); 
			squares[0][7] = factory( 'r', row, 7); 

			for (int col = 0; col < this->boardSize; ++col)
				this->blackPieces.push_back(squares[row][col]);
		}
		else if ( row == 7)
		{
			squares[7][0] = factory( 'R', row, 0); 
			squares[7][1] = factory( 'N', row, 1); 
			squares[7][2] = factory( 'B', row, 2); 
			squares[7][3] = factory( 'Q', row, 3); 
			squares[7][4] = factory( 'K', row, 4); 
			squares[7][5] = factory( 'B', row, 5); 
			squares[7][6] = factory( 'N', row, 6); 
			squares[7][7] = factory( 'R', row, 7); 

			for (int col = 0; col < this->boardSize; ++col)
				this->whitePieces.push_back(squares[row][col]);
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
					this->blackPieces.push_back(squares[row][col]);
				}	

				// The second to last row is full of white pawns
				else if (row == 6)
				{
					squares[row][col] = factory('P', row, col);
					this->whitePieces.push_back(squares[row][col]);
				}
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
        return ( manager.getTurn() == 'B' );

    return ( manager.getTurn() == 'W' );
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
	char opponentSymbol = (manager.getTurn() == 'W') ? 'P' : 'p';

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

Piece* Board::findPieceToMove(Coordinates cell, char pieceSymbol, MoveTypeSymbols moveType, char ambiguity)
{
	// Determines if I have to check the white or black pieces
	std::vector<Piece*> pieces = (manager.getTurn() == 'W') ? this->whitePieces : this->blackPieces;

	// Goes piece by piece checking if it is the right one
	for(auto iterator = this->whitePieces.begin(); iterator != this->whitePieces.end(); ++iterator)
	{
		if ((*iterator)->getSymbol() == pieceSymbol)
		{
			// Get the struct with all the moves in their own moveTypes vectors
			MoveTypes& moves = (*iterator)->getPossibleMoves();

			std::vector<Coordinates>* coordinates;

			// Gets the vector with the type of moves that we need to find
			switch(moveType)
			{
				case MoveTypeSymbols::commuting:  
					coordinates = &moves.commutingMoves; 
					break;

				case MoveTypeSymbols::capturing:  
					coordinates = &moves.capturingMoves; 
					break;

				case MoveTypeSymbols::promotion:  
					coordinates = &moves.promotionMoves;
					break;

				case MoveTypeSymbols::enPassant:
					coordinates = &moves.enPassantMoves;
					break;

				case MoveTypeSymbols::castle:
					coordinates = &moves.castle;
					break;
			}

			// We found a possible piece. check if it can move to the given cell
			for (auto moveIterator = coordinates->begin(); moveIterator != coordinates->end(); ++moveIterator )
			{
				if ( *moveIterator == cell)
					if (! ambiguity || ambiguity == moveIterator->getRow() || ambiguity == moveIterator->getFile())
						return *iterator;
			}
		}
	}

	// No piece was found
	return nullptr;
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

bool Board::isEnemy( Coordinates cell)
{
    // If it is out of boundaries or empty
    if ( cell.isOutOfBoundaries() || getSquare(cell) == nullptr)
        return false;

    /*
    Piece* piece = getSquare(cell);

    // If the piece is black, check if the cell is upper case
    if ( std::islower(piece->getSymbol() ) )
        return std::isupper(getSquare(row,file)->getSymbol());

    // Return true if the piece in the cell is the opposite color to this
    return std::isupper(getSquare(row,file)->getSymbol()); */

    return true;
}


bool Board::isUnderAttack(Coordinates cell)
{
	for ( int row = 0; row < boardSize; ++row)
	{
 		for ( int col = 0; col < boardSize; ++col)
 		{
 			Piece* pieceToCheck = this->squares[row][col];
 			if ( pieceToCheck )
 				if ( isEnemy(cell) )
 				{
 					;
 				}
 		}
	}

	return false;
}