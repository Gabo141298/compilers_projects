#include "Board.h"

#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

#include <cctype>

Piece* Board::factory(char symbol, int file, int rank)
{
	Coordinates position(rank,file);
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
	for (int file = 0; file < this->boardSize; ++file)
	{
		// Sets the pieces for the first and last files
		// Lower case means a black piece, upper case is a white piece
		if (file == 0)
		{
			squares[0][0] = factory( 'r', file, 0); 
			squares[0][1] = factory( 'n', file, 1); 
			squares[0][2] = factory( 'b', file, 2); 
			squares[0][3] = factory( 'q', file, 3); 
			squares[0][4] = factory( 'k', file, 4); 
			squares[0][5] = factory( 'b', file, 5); 
			squares[0][6] = factory( 'n', file, 6); 
			squares[0][7] = factory( 'r', file, 7); 

			for (int rank = 0; rank < this->boardSize; ++rank)
				this->blackPieces.push_back(squares[file][rank]);
		}
		else if ( file == 7)
		{
			squares[7][0] = factory( 'R', file, 0); 
			squares[7][1] = factory( 'N', file, 1); 
			squares[7][2] = factory( 'B', file, 2); 
			squares[7][3] = factory( 'Q', file, 3); 
			squares[7][4] = factory( 'K', file, 4); 
			squares[7][5] = factory( 'B', file, 5); 
			squares[7][6] = factory( 'N', file, 6); 
			squares[7][7] = factory( 'R', file, 7); 

			for (int rank = 0; rank < this->boardSize; ++rank)
				this->whitePieces.push_back(squares[file][rank]);
		}
		else 
		{
			// All the other files start with the same piece, either pawns or nothing
			for (int rank = 0; rank < this->boardSize; ++rank)
			{
				Coordinates position(file, rank);

				// The second file is full of black pawns
				if (file == 1)
				{
					squares[file][rank] = factory('p', file, rank);
					this->blackPieces.push_back(squares[file][rank]);
				}	

				// The second to last file is full of white pawns
				else if (file == 6)
				{
					squares[file][rank] = factory('P', file, rank);
					this->whitePieces.push_back(squares[file][rank]);
				}
				// All the other files have nothing
				else
					squares[file][rank] = nullptr;
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

void Board::deletePieceFromBoard(int file, int rank)
{
	std::vector<Piece*> pieces = (manager.getTurn() == 'W') ? this->whitePieces : this->blackPieces;
	
	for ( auto iterator = pieces.begin(); iterator != pieces.end(); ++iterator )
	{
		if ( (*iterator)->getFile() == file && (*iterator)->getRank() == rank)
			if ( manager.getTurn() == 'W')
				this->whitePieces.erase(iterator);
			else
				this->blackPieces.erase(iterator);

	}

    delete squares[file][rank];
    squares[file][rank] = nullptr;
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

bool Board::findPieceToMove(Coordinates cell, char pieceSymbol, MoveTypeSymbols moveType, char ambiguity, char promotionSymbol, CheckStates checkState)
{
    printBoard();

	// Determines if I have to check the white or black pieces
	std::vector<Piece*> pieces = (manager.getTurn() == 'W') ? this->whitePieces : this->blackPieces;

	//char charFile = cell.file+97;
	std::cout << "TURNO: " << manager.getTurn() << " Celda: " << cell <<  std::endl;

	// Goes piece by piece checking if it is the right one
	for(auto iterator = pieces.begin(); iterator != pieces.end(); ++iterator)
	{
		std::cout << "Currently printing the piece: " << (*iterator)->getSymbol() << " in cell: " << (*iterator)->getPosition() << std::endl;

		// Method that determines the possible moves of the piece in the current turn
		(*iterator)->calculatePossibleMoves();
	
		if ((*iterator)->getSymbol() == pieceSymbol)
		{
			// Get the struct with all the moves in their own moveTypes vectors
			MoveTypes& moves = (*iterator)->getPossibleMoves();

			std::vector<Coordinates>* coordinates;

			// Gets the vector with the type of moves that we need to find
			switch(moveType)
			{
				case MoveTypeSymbols::commuting:  
					//std::cout << "A commuting move" << std::endl;
					coordinates = &moves.commutingMoves; 
					break;

				case MoveTypeSymbols::capturing:  
					std::cout << "A capturing move" << std::endl;
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
				std::cout << "Possible move: " << (*iterator)->getSymbol() << " from: " << (*iterator)->getPosition() << " to: " << *moveIterator << std::endl;
		
				if ( *moveIterator == cell)
					if (! ambiguity || ambiguity == moveIterator->getFile() || ambiguity == moveIterator->getRank())
					{	
						// We found the right piece. Now make the move
						makeMove(*iterator, cell, moveType);

						// If it was written that the move was a check, it is validated here
						if ( checkState == CheckStates::check)
							validateCheck(*iterator);

						return true;
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
						if (!ambiguity || ambiguity == moveIterator->getFile() || ambiguity == moveIterator->getRank())
						{
							// The move made was indeed enPassant, not a regular capture
							moveType = MoveTypeSymbols::enPassant;

							// We found the right piece. Now make the move
							makeMove(*iterator, cell, moveType);

							// If it was written that the move was a check, it is validated here
							if ( checkState == CheckStates::check)
								validateCheck(*iterator);

							return true;
						}
					}
				}
			}
		}
	}

	// No piece was found
	return false;
}

void Board::makeMove(Piece* piece, Coordinates cell, MoveTypeSymbols moveType, char promotionSymbol)
{

	//std::cout << "PIECE: " << piece->getSymbol() << " CELL: " << cell.getFile() << cell.getRank() << std::endl;

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
    
    else if ( moveType == MoveTypeSymbols::promotion || moveType == MoveTypeSymbols::capturingPromotion)
    {
        // Delete the pawn from the board
        delete squares[piece->getPosition().file][piece->getPosition().file];

        short file = cell.getFile(); short rank = cell.getRank();

        // Makes sure the piece is of the right color
        char newSymbol = (manager.getTurn() == 'W') ? toupper(promotionSymbol) : tolower(promotionSymbol);

        // In case the promotion was also a capture, we have to delete the previous piece
        if ( moveType == MoveTypeSymbols::capturingPromotion)
        	deletePieceFromBoard(file, file);

        // Create the new piece in the 
        squares[file][file] = factory( newSymbol, file, file);
    }


    // The en passant rule only applies for one turn. So, it has to be cancelled after every move.
    resetOpponentEnPassants();

    // Change turns
    manager.changeTurn();

    // Check if the game ended
    manager.setGameState();
}

void Board::relocatePiece(Piece* piece, Coordinates cell, bool deletePiece)
{
	short file = piece->getFile();
	short rank = piece->getRank();

	// The piece is no longer in this position
	squares[file][rank] = nullptr;

	// This is when there was a capture, so the piece has to be removed
	if (deletePiece)
		deletePieceFromBoard( cell.getFile(), cell.getRank() );

	// Now the board has the piece in the new position
	squares[cell.getFile()][cell.getRank()] = piece;

	// Call the method so that the piece knows its new place
	piece->setPosition(cell);
}

Board::~Board()
{
	for (int file = 0; file < boardSize; ++file)
	{
		for (int rank = 0; rank < boardSize; ++rank)
		{
			delete this->squares[file][rank];
		}
	}
}

std::ostream& operator<<(std::ostream &out, const Board &board)
{
	for(int file = 0; file < board.boardSize; ++file)
	{
 		for(int rank = 0; rank < board.boardSize; ++rank)
 		{
 			if(board.squares[file][rank] == nullptr)
 				out << '_';
 			else
 				out	 << *board.squares[file][rank];
 			out << ' ';
 		}
 		out << std::endl;
	}

	return out;
}

Coordinates Board::getKingPosition()
{
	// Gets the symbol of the king of the opposite rankor
	char kingSymbol = (manager.getTurn() == 'W') ? 'k' : 'K';

	for ( short file = 0; file < 8; ++file)
		for ( short rank = 0; file < 8; ++file)
			if ( this->squares[file][rank]->getSymbol() == kingSymbol) 
				return Coordinates(file,rank);

	// It should never get to this point
	return Coordinates(0,0);
}

bool Board::validateCheck(Piece* piece)
{
	MoveTypes moves = piece->getPossibleMoves();

	Coordinates kingPosition = getKingPosition();

	// Check the regular capturing moves to see if this piece threatens the king
	for ( auto iterator = moves.capturingMoves.begin(); iterator != moves.capturingMoves.end(); ++iterator)
		// If the piece is attacking the square where the king is
		if ( *iterator == kingPosition )
			return true;

	return false;
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
        return std::isupper(getSquare(file,file)->getSymbol());

    // Return true if the piece in the cell is the opposite rankor to this
    return std::isupper(getSquare(file,file)->getSymbol()); */

    return true;
}


bool Board::isUnderAttack(Coordinates cell)
{
	for ( int file = 0; file < boardSize; ++file)
	{
 		for ( int rank = 0; rank < boardSize; ++rank)
 		{
 			Piece* pieceToCheck = this->squares[file][rank];
 			if ( pieceToCheck )
 				if ( isEnemy(cell) )
 				{
 					;
 				}
 		}
	}

	return false;
}

void Board::printBoard()
{
	for ( int file = 0; file < boardSize; ++file)
	{
 		for ( int rank = 0; rank < boardSize; ++rank)
 		{
 			if ( squares[file][rank])
 				std::cout << squares[file][rank]->getSymbol() << " ";
 			else 
 				std::cout << "- ";
 		}
 		std::cout << std::endl;
	}
}