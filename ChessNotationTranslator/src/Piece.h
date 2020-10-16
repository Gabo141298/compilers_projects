#ifndef PIECE_H
#define PIECE_H

#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

class Board;

/// Struct that stores the rank and file of a cell in the board.
struct Coordinates
{
    short file;
    short rank;

    // Conversion constructor
    Coordinates(short rank = 0, short file = 0)
    : file { file }
    , rank { rank }
    {}

    inline  bool isOutOfBoundaries()
    {
        return (rank < 0 || rank > 7 || file < 0 || file > 7);
    }

    friend bool operator==(Coordinates& coordinate, Coordinates& other)
    {
        return ( (coordinate.rank == other.rank) && (coordinate.file == other.file) );
    }

    inline short getRank() { return this->rank; }

    inline short getFile() { return this->file; }

    friend std::ostream& operator<<(std::ostream &out, const Coordinates &coordinate)
    {
        return out << "(" << char(coordinate.file + 97) << "," << abs(coordinate.rank-8) << ')' ;
    }
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
    commuting, capturing, enPassant, promotion, shortCastle, longCastle, capturingPromotion
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
    * @param rank The rank to check in the board.
    * @param file The file to check in the board.
    * @return true if the given cell is a nullptr (there is no piece).
    */
    bool isFree(short file, short rank);

  	/*! 
    * @brief Checks if a given cell has a piece that belongs to the opponent.
    *        As White pieces are uppercase and black pieces lower case, if this
    *        symbol is upper case, it has to check if the other's symbol is 
    *        lower case, and viceversa.
    * @param rank The rank to check in the board.
    * @param file The file to check in the board.
    * @return true if the color of the piece in the coordinates given
    *         is opposite to "this" piece's color.
    *         false if it has the same color or is empty.
    */
    bool isEnemy( short file, short rank);

  	friend std::ostream& operator<<(std::ostream &out, const Piece &piece);

    /*!
    * @brief determine the moves that the piece can make and store them 
    * in the appropiate MoveTypes and possibleMoves vectors
    */
  	virtual void calculatePossibleMoves() = 0;

    /// Returns the struct with all the possible moves this piece can make
    inline MoveTypes& getPossibleMoves() { return this->possibleMoves; }

  	/// Returns the symbol of the piece ( 'p', 'K', 'r', etc. )
    inline char getSymbol() const { return this->symbol; }

    /// Returns the attribute rank from the current position of the piece
    inline int getRank() const { return currentPosition.rank; }

    /// Returns the attribute file from the current position of the piece
    inline int getFile() const { return currentPosition.file; }

    /// Changes the position from the piece to new Coordinates
    inline void setPosition(Coordinates newPosition) {currentPosition = newPosition; }

    /// Returns the Coordinates struct of the piece
    inline Coordinates getPosition() const { return this->currentPosition; }

    /// This is needed for the pawns
    inline void resetJustMovedTwice() {}

};

#endif