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

void Board::deletePieceFromBoard(int row, int col)
{
	std::vector<Piece*> pieces = (manager.getTurn() == 'W') ? this->whitePieces : this->blackPieces;
	
	for ( auto iterator = pieces.begin(); iterator != pieces.end(); ++iterator )
	{
		if ( (*iterator)->getRow() == row && (*iterator)->getFile() == col)
			if ( manager.getTurn() == 'W')
				this->whitePieces.erase(iterator);
			else
				this->blackPieces.erase(iterator);

	}

    delete squares[row][col];
    squares[row][col] = nullptr;
}

void Board::movePieceIfPossible(Piece* selectedPiece, int rowPos, int colPos)
{
    bool validMove = false;

    // Checks if the move made by the player was any of the commuting moves
    for(unsigned int index = 0; index < validMoves.commutingMoves.size() && !validMove; ++index)
    {
        if(colPos == validMoves.commutingMoves[index].file && rowPos == validMoves.commutingMoves[index].row)
        {
            relocatePiece(selectedPiece, Coordinates(rowPos,colPos));
            validMove = true;
        }
    }

    // Checks if the move made was a capture to another piece
    for(unsigned int index = 0; index < validMoves.capturingMoves.size() && !validMove; ++index)
    {
        if(colPos == validMoves.capturingMoves[index].file && rowPos == validMoves.capturingMoves[index].row)
        {
        	deletePieceFromBoard(rowPos, colPos);

            // Makes the move from the last piece to the chosen cell
            relocatePiece(selectedPiece, Coordinates(rowPos,colPos));
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
	// Get all the pieces from the opponent
	std::vector<Piece*> pieces = (manager.getTurn() == 'W') ? this->whitePieces : this->blackPieces;

	// Iterate through the opponent's pieces
	for ( auto iterator = pieces.begin(); iterator != pieces.end(); ++iterator)
	{
		// Get the piece symbol in upper case and check if it is a pawn
		if ( toupper( (*iterator)->getSymbol() ) == 'P') 
		{
			// Set the justMovedTwice attribute to 0, so that the pawn cannot be taken en passant anymore
			(*iterator)->resetJustMovedTwice(); 
		}
	}
}

Piece* Board::findPieceToMove(Coordinates cell, char pieceSymbol, MoveTypeSymbols moveType, char ambiguity, char promotionSymbol, CheckStates checkState)
{
	// We don't care about the color right now, 
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

				case MoveTypeSymbols::shortCastle:
					cell = (manager.getTurn() == 'W') ? Coordinates(7,6) : Coordinates(0,6);
					coordinates = &moves.castle;
					break;

				case MoveTypeSymbols::longCastle:
					cell = (manager.getTurn() == 'W') ? Coordinates(7,3) : Coordinates(0,3);
					coordinates = &moves.castle;
					break;
			}

			// We found a possible piece. check if it can move to the given cell
			for (auto moveIterator = coordinates->begin(); moveIterator != coordinates->end(); ++moveIterator )
			{
				if ( *moveIterator == cell)
					if (! ambiguity || ambiguity == moveIterator->getRow() || ambiguity == moveIterator->getFile())
					{	
						// We found the right piece. Now make the move
						makeMove(*iterator, cell, moveType);
						return *iterator;
					}
			}

			// The enPassant move is not explicitaly said, we must check it here if there was a pawn capture
			if ( moveType == MoveTypeSymbols::capturing && pieceSymbol == 'P')
			{
				coordinates = &moves.enPassantMoves;

				// We found a possible piece. check if it can move to the given cell
				for (auto moveIterator = coordinates->begin(); moveIterator != coordinates->end(); ++moveIterator )
				{
					// The coordinate is the same as the one we want to find
					if ( *moveIterator == cell)
					{
						// There was no abiguity, or there was one and the move found was in the right position
						if (!ambiguity || ambiguity == moveIterator->getRow() || ambiguity == moveIterator->getFile())
						{
							// The move made was indeed enPassant, not a regular capture
							moveType = MoveTypeSymbols::enPassant;

							// We found the right piece. Now make the move
							makeMove(*iterator, cell, moveType);
							return *iterator;
						}
					}
				}
			}
		}
	}

	// No piece was found
	return nullptr;
}

void Board::makeMove(Piece* piece, Coordinates cell, MoveTypeSymbols moveType)
{
	// If the move was only moving a piece to a different square
	if ( moveType == MoveTypeSymbols::commuting)
	{
		// This is the easiest case, we just have to move the piece to the new square
		relocatePiece(piece, cell);
	}
	else if ( moveType == MoveTypeSymbols::capturing)
	{
		// This is the second easiest move, we move the piece and delete the last one
		// the true parameter is to let it know there was a capture
		relocatePiece(piece, cell, true);
	}
    // If the piece is a pawn, and it is in the last rank, a promotion move ocurred
    if ( ( piece->getSymbol() == 'P' || piece->getSymbol() == 'p') )
    {
        // Delete the pawn from the board
        delete squares[piece->getPosition().row][piece->getPosition().file];
        /*

        // The new piece will be either a black or a white queen
        char newSymbol = (rowPos) ? 'q' : 'Q';

        // Creates the piece and assign it a Queen image
        squares[rowPos][colPos] = piece = new Queen(newSymbol, this, piece->getPosition());
        */
    }
}

void Board::relocatePiece(Piece* piece, Coordinates cell, bool deletePiece)
{
	short row = piece->getRow();
	short file = piece->getFile();

	// The piece is no longer in this position
	squares[row][file] = nullptr;

	// This is when there was a capture, so the piece has to be removed
	if (deletePiece)
		deletePieceFromBoard( cell.getRow(), cell.getFile() );

	// Now the board has the piece in the new position
	squares[cell.getRow()][cell.getFile()] = piece;

	// Call the method so that the piece knows its new place
	piece->setPosition(cell);
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