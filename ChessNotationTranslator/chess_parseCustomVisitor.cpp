#include <vector>
#include <iostream>

#include "chess_parseCustomVisitor.h"
#include "./src/SemanticAnalyzer.h"

antlrcpp::Any chess_parseCustomVisitor::visitGame(chess_parseParser::GameContext *ctx)  
{
	SemanticAnalyzer* semanticAnalyzer = new SemanticAnalyzer();

	semanticAnalyzer->header.tournament = ctx->header()->ID(0)->getText();
	semanticAnalyzer->header.date = ctx->header()->DATE()->getText();
	semanticAnalyzer->header.round = stoi(ctx->header()->NUMBER()->getText());
	semanticAnalyzer->header.whitesPlayer = ctx->header()->ID(1)->getText();
	semanticAnalyzer->header.blacksPlayer = ctx->header()->ID(2)->getText();

		

	antlrcpp::Any result = semanticAnalyzer;
	return result;
}