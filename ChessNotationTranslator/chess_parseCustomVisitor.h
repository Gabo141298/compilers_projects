#pragma once

#include "antlr4-runtime.h"
#include "chess_parseBaseVisitor.h"
#include "./src/SemanticAnalyzer.h"


class chess_parseCustomVisitor  : public chess_parseBaseVisitor
{
private:
SemanticAnalyzer* semanticAnalyzer;
const char pieceSymbols [10]= {'\0', '\0','N', 'K', 'B', 'R', 'P', '\0', '\0', 'Q'};

private:

	endResult getWinner(chess_parseParser::GameContext *ctx);
	void fillHeader(chess_parseParser::GameContext *ctx);


public:
	antlrcpp::Any visitGame(chess_parseParser::GameContext *ctx) override ;
	antlrcpp::Any visitHeader(chess_parseParser::HeaderContext *ctx) override;
	antlrcpp::Any visitPlay(chess_parseParser::PlayContext *ctx) override ;
	virtual ~chess_parseCustomVisitor () {}
};
