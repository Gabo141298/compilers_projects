#include "Board.h"
#include "SemanticAnalyzer.h"

#include <iostream>


std::ostream& operator<<(std::ostream& stream, const Header& header)
{
	stream << "[Event " << header.tournament << "]" << std::endl;
	stream << "[Date \"" << header.date << "\"]"<< std::endl;
	stream << "[Round \"" << header.round << "\"]"<< std::endl;
	stream << "[White \"" << header.whitesPlayer << "\"]"<< std::endl;
	stream << "[Black \"" << header.blacksPlayer << "\"]"<< std::endl;

	return stream;
}

std::ostream& operator<<(std::ostream& stream, const SemanticAnalyzer& analyzer)
{
	stream << analyzer.header << analyzer.board << std::endl;
	return stream;
}