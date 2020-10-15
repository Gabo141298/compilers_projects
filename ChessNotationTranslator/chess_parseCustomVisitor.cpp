#include <vector>
#include <iostream>

#include "chess_parseCustomVisitor.h"
#include "./src/SemanticAnalyzer.h"


endResult getWinner(chess_parseParser::GameContext *ctx)
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

antlrcpp::Any chess_parseCustomVisitor::visitGame(chess_parseParser::GameContext *ctx)  
{
	SemanticAnalyzer* semanticAnalyzer = new SemanticAnalyzer();

	semanticAnalyzer->header.tournament = ctx->header()->ID(0)->getText();
	semanticAnalyzer->header.date = ctx->header()->DATE()->getText();
	semanticAnalyzer->header.round = stoi(ctx->header()->NUMBER()->getText());
	semanticAnalyzer->header.whitesPlayer = ctx->header()->ID(1)->getText();
	semanticAnalyzer->header.blacksPlayer = ctx->header()->ID(2)->getText();
	semanticAnalyzer->header.result = getWinner(ctx);



		

	antlrcpp::Any result = semanticAnalyzer;
	return result;
}