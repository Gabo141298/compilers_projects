#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

#include <iostream>

class Board
{
  private: 
  	Piece* squares[8][8];

  public: 
  	Board();

  	~Board();


  private: 

  public:
  	const static unsigned char boardSize = 8;
  	friend std::ostream& operator<<(std::ostream &out, const Board& board);

};

#endif