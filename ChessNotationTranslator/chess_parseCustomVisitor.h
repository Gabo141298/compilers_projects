#pragma once

#include "antlr4-runtime.h"
#include "chess_parseBaseVisitor.h"

class chess_parseCustomVisitor  : public chess_parseBaseVisitor
{
public:
	antlrcpp::Any visitGame(chess_parseParser::GameContext *ctx) override ;

	virtual ~chess_parseCustomVisitor () {}
};
