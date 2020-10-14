#include <vector>
#include <iostream>

#include "chess_parseCustomVisitor.h"


antlrcpp::Any chess_parseCustomVisitor::visitGame(chess_parseParser::GameContext *ctx)  
{
	std::cout << ctx->header()->ID(1)->getText();

	return antlrcpp::Any();
}