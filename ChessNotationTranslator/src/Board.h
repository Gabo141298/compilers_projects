#ifndef BOARD_H
#define BOARD_H

#include "ChessManager.h"
#include "Piece.h"

#include <iostream>
#include <list>

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
  	Piece* factory(char symbol, int row, int col);

    void deletePieceFromBoard(int row, int col);

    /// En passants only last one move. This method resets if after every turn
    void resetOpponentEnPassants();

  public:
  	/// Defines the board size. Really, it's not going to change
    const static unsigned char boardSize = 8;
    
    /// Overload of the print operator
  	friend std::ostream& operator<<(std::ostream &out, const Board& board);

    /// Get method for a piece in the board, given a row and a file
    inline Piece* getSquare(int row, int col) { return this->squares[row][col]; }

    /// Get method for a piece in the board, given a coordinate
    inline Piece* getSquare(Coordinates cell) { return this->squares[cell.row][cell.file]; }

    /// Checks if the current player in turn corresponds with the color of the piece selected
    bool isRightTurn(Piece* selectedPiece);

    /// It checks if the piece can be moved to the position given by rowPos and colPos.
    /// If it can be moved, it will move the piece.
    void movePieceIfPossible(Piece* selectedPiece, int rowPos, int colPos);

    /// It tells the piece to move the position given by rowPos, and colPos.
    /// It also does changes to boardState to update the pieces positions.
    void movePiece(Piece* selectedPiece, int rowPos, int colPos);

    /// Checks if the game ended. If it ended, then it creates the PGN file, as it was a valid game.
    void checkIfGameEnded();

    /// Checks if a piece is an enemy, depending on a color. If 
    bool isEnemy(Coordinates cell);

    /// Checks if any given square is being attacked by opponent pieces. Useful for king moves. 
    bool isUnderAttack(Coordinates cell);

    /// This is for the semantic analysis. It finds the piece that the player wanted to move by
    /// looking at what piece can move to the given cell. It receives the piece symbol
    Piece* findPieceToMove(Coordinates cell, char pieceSymbol, MoveTypeSymbols moveType, char ambiguity = '\0');
};

#endif