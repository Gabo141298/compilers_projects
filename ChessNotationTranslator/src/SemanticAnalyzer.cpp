#include "Board.h"
#include "SemanticAnalyzer.h"

#include <iostream>


std::ostream& operator<<(std::ostream& stream, const Header& header)
{
	stream << "[Event " << header.tournament << "]" << std::endl;
	stream << "[Site " << header.site << "]" << std::endl;
	stream << "[Date \"" << header.date << "\"]"<< std::endl;
	stream << "[Round \"" << header.round << "\"]"<< std::endl;
	stream << "[White " << header.whitesPlayer << "]"<< std::endl;
	stream << "[Black " << header.blacksPlayer << "]"<< std::endl;
	if(header.result != endResult::EnCurso)
	{
		stream<< "[Result \"";
		switch (header.result)
		{	
		case endResult::Empate :
			stream << "1/2-1/2";
			break;
		case endResult::GananBlancas:
			stream << "1-0";
			break;
		case endResult::GananNegras:
			stream << "0-1";
			break;
		}
		stream << "\"]" << std::endl;
	}

	return stream;
}

std::ostream& operator<<(std::ostream& stream, SemanticAnalyzer& analyzer)
{
	// std::cout << "Holaaa";
	stream << analyzer.header ;
	char ch;
	while(analyzer.gameStream.get(ch) )
		stream << ch;

	if(analyzer.header.result != endResult::EnCurso)
	{
		switch (analyzer.header.result)
		{	
		case endResult::Empate :
			stream << "1/2-1/2";
			break;
		case endResult::GananBlancas:
			stream << "1-0";
			break;
		case endResult::GananNegras:
			stream << "0-1";
			break;
		}
	}
	stream << std::endl;
	return stream;
}