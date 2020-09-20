#ifndef PIECE_H
#define PIECE_H

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

/// Struct that stores the row and file of a cell in the board.
struct Coordinates
{
    short row;
    short file;

    // Conversion constructor
    Coordinates(short row = 0, short file = 0)
    : row { row }
    , file { file }
    {}
};

/** Struct that  stores two arrays,  each with different types
 *  of moves. The first one, "commutingMoves",  are moves that
 *  the piece can make to an empty cell. The other, "capturing
 *  "moves", are moves when the piece moves and captures a pie
 *  ce in another cell.
 */
 struct MoveTypes
 {
     std::vector<Coordinates> commutingMoves;
     std::vector<Coordinates> capturingMoves;
 };

class Piece
{
  protected: 
  	/// The piece has to know its current position in the board
    Coordinates currentPosition;

  	/// The symbol of the piece ( 'K','Q','R','B','N','P', etc).
  	char symbol;

  	/// A matrix that contains pointers to the pieces in the game.
    Piece*** board;

  public: 
  	Piece(){}

  	explicit Piece(char symbol)
  	: symbol{symbol}
  	{

  	}
  	
  	/*! 
    * @brief Checks if a given cell in the board is empty.
    * @param row The row to check in the board.
    * @param file The file to check in the board.
    * @return true if the given cell is a nullptr (there is no piece).
    */
    bool isFree(short row, short file);

  	/*! 
    * @brief Checks if a given cell has a piece that belongs to the opponent.
    *        As White pieces are uppercase and black pieces lower case, if this
    *        symbol is upper case, it has to check if the other's symbol is 
    *        lower case, and viceversa.
    * @param row The row to check in the board.
    * @param file The file to check in the board.
    * @return true if the color of the piece in the coordinates given
    *         is opposite to "this" piece's color.
    *         false if it has the same color or is empty.
    */
    bool isEnemy( short row, short file);

  	friend std::ostream& operator<<(std::ostream &out, const Piece &piece);

  	virtual MoveTypes getPossibleMoves() = 0;

  	/// Returns the symbol of the piece ( 'p', 'K', 'r', etc. )
    inline char getSymbol() const { return this->symbol; }

    inline int currentX() const { return currentPosition.file; }
    inline int currentY() const { return currentPosition.row; }

    void setPosition(Coordinates newPosition);

};

#endif