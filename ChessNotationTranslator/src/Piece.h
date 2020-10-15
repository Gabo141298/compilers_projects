#ifndef PIECE_H
#define PIECE_H

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

class Board;

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

    inline  bool isOutOfBoundaries()
    {
        return (row < 0 || row > 7 || file < 0 || file > 7);
    }

    friend bool operator==(Coordinates& coordinate, Coordinates& other)
    {
        return ( (coordinate.row == other.row) && (coordinate.file == other.file) );
    }

    inline short getRow() { return this->row; }

    inline short getFile() { return this->file; }
};

/** Struct that  stores 5 arrays,  each with different types
 *  of moves. The first one, "commutingMoves",  are moves that
 *  the piece can make to an empty cell. The second, "capturing
 *  "moves", are moves when the piece moves and captures a piece 
 *  in another cell. The third and four are special moves only
 *  pawns can make. The last one is a special move only the king
 *  can make.
 */
 struct MoveTypes
 {
     std::vector<Coordinates> commutingMoves;
     std::vector<Coordinates> capturingMoves;
     std::vector<Coordinates> enPassantMoves;
     std::vector<Coordinates> promotionMoves;
     std::vector<Coordinates> castle;
 };

enum MoveTypeSymbols
{
    commuting, capturing, enPassant, promotion, castle
};

class Piece
{
  protected: 
  	/// The symbol of the piece ( 'K','Q','R','B','N','P', etc).
  	char symbol;

  	/// A matrix that contains pointers to the pieces in the game.
    Board* board;

    /// The piece has to know its current position in the board
    Coordinates currentPosition;

    /// Stores the moves this piece can move to
    MoveTypes possibleMoves;

  public: 
  	Piece(){}

    virtual ~Piece(){}

    /// A piece requires its symbol, the board to access which squares have
    /// which pieces, and the currentPosition to know where they start
  	explicit Piece(char symbol, Board* board, Coordinates currentPosition)
  	: symbol{symbol}, 
      board(board), 
      currentPosition(currentPosition)
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

  	virtual void calculatePossibleMoves() = 0;

    inline MoveTypes& getPossibleMoves() { return this->possibleMoves; }

  	/// Returns the symbol of the piece ( 'p', 'K', 'r', etc. )
    inline char getSymbol() const { return this->symbol; }

    inline int currentX() const { return currentPosition.file; }
    inline int currentY() const { return currentPosition.row; }

    inline void setPosition(Coordinates newPosition) {currentPosition = newPosition; }

    /// Returns the Coordinates struct of the piece
    inline Coordinates getPosition() const { return this->currentPosition; }

};

#endif