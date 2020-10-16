#ifndef BOARD_H
#define BOARD_H

#include "ChessManager.h"
#include "Piece.h"

#include <iostream>
#include <list>

enum CheckStates
{
    none, check, mate
};

class Board
{
  private: 
    /// This is the 8 by 8 board that stores all the pieces
  	Piece* squares[8][8];

    /// It keeps track of the remaining pieces of each player, the current turn and if the game ended.
    ChessManager manager;

    /// Keeps the valid moves from the last selected piece.
    MoveTypes validMoves;

    /// Keeps track of all the squares that are under attack by black
    std::list<Coordinates> squaresAttackedByBlack; 

    /// Keeps track of all the squares that are under attack by white
    std::list<Coordinates> squaresAttackedByWhite; 

    /// Stores the white pieces
    std::vector<Piece*> whitePieces; 

    /// Stores the black pieces
    std::vector<Piece*> blackPieces;


  public: 
  	Board();

  	~Board();


  private: 
  	Piece* factory(char symbol, int file, int rank);

    /// Removes a piece from the board and deletes it from memory
    void deletePieceFromBoard(int file, int rank);

    /// En passants only last one move. This method resets if after every turn
    void resetOpponentEnPassants();

    /// Method to move a piece from one square of the board to another
    void relocatePiece(Piece* piece, Coordinates cell, bool deletePiece = false);

    /// Make the move, whether it's enPassant, commute, capture, promotion or castle
    void makeMove(Piece* piece, Coordinates cell, MoveTypeSymbols moveType, char promotionSymbol = 'Q');

    /// Checks that if a check is written, the move actually attacks the king (it is a check)
    bool validateCheck(Piece* piece);

    /// Gets the position of the enemy king
    Coordinates getKingPosition();

  public:
  	/// Defines the board size. Really, it's not going to change
    const static unsigned char boardSize = 8;
    
    /// Overload of the print operator
  	friend std::ostream& operator<<(std::ostream &out, const Board& board);

    /// Get method for a piece in the board, given a row and a file
    inline Piece* getSquare(int file, int rank) { return this->squares[file][rank]; }

    /// Get method for a piece in the board, given a coordinate
    inline Piece* getSquare(Coordinates cell) { return this->squares[cell.file][cell.rank]; }

    /// Checks if the current player in turn corresponds with the color of the piece selected
    bool isRightTurn(Piece* selectedPiece);

    /// Checks if the game ended. If it ended, then it creates the PGN file, as it was a valid game.
    void checkIfGameEnded();

    /// Checks if a piece is an enemy, depending on a color. If 
    bool isEnemy(Coordinates cell);

    /// Checks if any given square is being attacked by opponent pieces. Useful for king moves. 
    bool isUnderAttack(Coordinates cell);

    /// This is for the semantic analysis. It finds the piece that the player wanted to move by
    /// looking at what piece can move to the given cell. It receives the piece symbol
    bool findPieceToMove(Coordinates cell, char pieceSymbol, MoveTypeSymbols moveType, char ambiguity = '\0', char promotionSymbol = 'Q', CheckStates checkState = CheckStates::none);
};

#endif