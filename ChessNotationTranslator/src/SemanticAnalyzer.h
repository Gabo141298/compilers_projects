#pragma once

#include "Board.h"

#include <iostream>
#include <sstream>
#include <string>

class chess_parseCustomVisitor;

enum endResult{Empate, GananBlancas, GananNegras, EnCurso};

struct Header
{
	std::string tournament;
	std::string date;
	int round;
	std::string whitesPlayer;
	std::string blacksPlayer;
	endResult result;		
	friend std::ostream& operator<<(std::ostream& stream, const Header& analyzer);

};

class SemanticAnalyzer
{
	friend class chess_parseCustomVisitor;

	Header header;
	Board board;

	std::stringstream gameStream;
	friend std::ostream& operator<<(std::ostream& stream, SemanticAnalyzer& analyzer);
};