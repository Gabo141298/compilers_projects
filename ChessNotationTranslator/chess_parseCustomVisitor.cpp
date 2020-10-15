#include <vector>
#include <iostream>

#include "chess_parseCustomVisitor.h"
#include "chess_parseLexer.h"
#include "./src/SemanticAnalyzer.h"


endResult chess_parseCustomVisitor::getWinner(chess_parseParser::GameContext *ctx)
{
	std::string result_text = ctx->GAME_END()->getText();
	if(result_text == "Ganan blancas")
		return endResult::GananBlancas;
	else if(result_text == "Ganan negras")
		return endResult::GananNegras;
	else if( result_text == "Empate")
		return endResult::Empate;
	else 
		return endResult::EnCurso;
}

void chess_parseCustomVisitor::fillHeader(chess_parseParser::GameContext *ctx)
{
	semanticAnalyzer->header.tournament = ctx->header()->ID(0)->getText();
	semanticAnalyzer->header.date = ctx->header()->DATE()->getText();
	semanticAnalyzer->header.round = stoi(ctx->header()->NUMBER()->getText());
	semanticAnalyzer->header.whitesPlayer = ctx->header()->ID(1)->getText();
	semanticAnalyzer->header.blacksPlayer = ctx->header()->ID(2)->getText();
	semanticAnalyzer->header.result = getWinner(ctx);
}


antlrcpp::Any chess_parseCustomVisitor::visitGame(chess_parseParser::GameContext *ctx)  
{
	this->semanticAnalyzer = new SemanticAnalyzer();

	fillHeader(ctx);
	
	// std::cout << ctx->getChildCount()  << std::endl;

	visitChildren(ctx);
	// {
	// 	case chess_parse.PAWN:
	// 		std::cout << "Yes" << std::endl;
	// }

	antlrcpp::Any result = semanticAnalyzer;
	return result;
}
antlrcpp::Any chess_parseCustomVisitor::visitHeader(chess_parseParser::HeaderContext *ctx)
{
	return 0;
}


antlrcpp::Any chess_parseCustomVisitor::visitPlay(chess_parseParser::PlayContext *ctx)  
{
	visitChildren(ctx);	

	
	return 0;
}


