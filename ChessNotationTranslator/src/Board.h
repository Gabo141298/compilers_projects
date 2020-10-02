#ifndef BOARD_H
#define BOARD_H

#include "ChessManager.h"
#include "Piece.h"

#include <iostream>

class Board
{
  private: 
    /// This is the 8 by 8 board that stores all the pieces
  	Piece* squares[8][8];

    /// It keeps track of the remaining pieces of each player, the current turn and if the game ended.
    ChessManager manager;

    /// Keeps the valid moves from the last selected piece.
    MoveTypes validMoves;

  public: 
  	Board();

  	~Board();


  private: 
  	Piece* factory(char symbol, int row, int col);

  public:
  	/// Defines the board size. Really, its not going to change
    const static unsigned char boardSize = 8;
    
    /// Overload of the print operator
  	friend std::ostream& operator<<(std::ostream &out, const Board& board);

    /// Overload of the brackets
    inline Piece* getSquare(int row, int col) { return this->squares[row][col]; }

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

    /// En passants only last one move. This method resets if after every turn
    void resetOpponentEnPassants();

      /// It assigns to selectedPiece the piece that is in the position given by rowPos and colPos.
    void savePieceIfPossible(Piece* selectedPiece, int rowPos, int colPos);

};

#endif