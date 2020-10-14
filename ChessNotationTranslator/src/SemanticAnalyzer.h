#pragma once

#include "Board.h"

#include <iostream>
#include <string>

class chess_parseCustomVisitor;

struct Header
{
	std::string tournament;
	std::string date;
	int round;
	std::string whitesPlayer;
	std::string blacksPlayer;	
	friend std::ostream& operator<<(std::ostream& stream, const Header& analyzer);

};

class SemanticAnalyzer
{
	friend class chess_parseCustomVisitor;

	Header header;
	Board board;

	friend std::ostream& operator<<(std::ostream& stream, const SemanticAnalyzer& analyzer);
};