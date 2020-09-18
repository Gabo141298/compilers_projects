#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>

class Piece
{
  protected: 
  	/// The symbol of the piece ( 'K','Q','R','B','N','P', etc).
  	char symbol;

  public: 
  	Piece(){}

  	explicit Piece(char symbol)
  	: symbol{symbol}
  	{

  	}

  	friend std::ostream& operator<<(std::ostream &out, const Piece &piece);

};

#endif