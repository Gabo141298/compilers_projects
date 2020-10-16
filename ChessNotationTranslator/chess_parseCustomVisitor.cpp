#include <vector>
#include <iostream>

#include "antlr4-runtime.h"
#include "chess_parseCustomVisitor.h"
#include "chess_parseLexer.h"
#include "./src/SemanticAnalyzer.h"

#include "src/Board.h"
#include "src/Piece.h"


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
	// std::cout << visitChildren(ctx) ;
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
	Coordinates cell;
	char pieceSymbol;
	MoveTypeSymbols moveType;
	short ambiguity = '\0';
	char promotionSymbol = 'Q';
	CheckStates checkState;

	if(ctx->JAQUE())
		checkState = CheckStates::check;
	else if(ctx->MATE())
		checkState = CheckStates::mate;
	else
		checkState = CheckStates::none;

	if(ctx->move()->children[0]->getText() == "Enroque corto")
	{
		// std::cout << "Enroque corto" << std::endl;
		pieceSymbol = 'K';
		moveType = shortCastle;
	}
	else if(ctx->move()->children[0]->getText() == "Enroque largo")
	{
		// std::cout << "Enroque largo" << std::endl;
		pieceSymbol = 'K';
		moveType = longCastle;
	}
	else
	{
		if(auto context = dynamic_cast<chess_parseParser::PromotionContext*>(ctx->move()->children[0]))
		{
			pieceSymbol = 'P' ;
			if(context->CAPTURES())
				moveType = MoveTypeSymbols::capturingPromotion;
			else
				moveType = MoveTypeSymbols::promotion;			
			cell.row = context->square()->RANK()->getText()[0]-48;
			cell.file = context->square()->FILE()->getText()[0]-97;
			// std::cout << pieceSymbol << context->square()->RANK()->getText()[0] << cell.row << "|" << context->square()->FILE()->getText()[0]<< cell.file << std::endl;
			if(context->in_position())
				ambiguity = context->in_position()->RANK()? context->in_position()->RANK()->getText()[0] : context->in_position()->FILE()->getText()[0];
			promotionSymbol = pieceSymbols[static_cast<antlr4::tree::TerminalNode *>(context->promotion_piece()->children[0])->getSymbol()->getType()];
		} 
		else if(auto context = dynamic_cast<chess_parseParser::CommuteContext*>(ctx->move()->children[0]))
		{
			pieceSymbol = pieceSymbols[static_cast<antlr4::tree::TerminalNode *>(context->piece()->children[0])->getSymbol()->getType()];
			// std::cout << pieceSymbol << std::endl;
			moveType = MoveTypeSymbols::commuting;			
			cell.row = context->square()->RANK()->getText()[0]-48;
			cell.file = context->square()->FILE()->getText()[0]-97;
			// std::cout << pieceSymbol << context->square()->RANK()->getText()[0] << cell.row << "|" << context->square()->FILE()->getText()[0]<< cell.file << std::endl;
			if(context->in_position())
				ambiguity = context->in_position()->RANK()? context->in_position()->RANK()->getText()[0]: context->in_position()->FILE()->getText()[0];
		} 
		else if(auto context = dynamic_cast<chess_parseParser::CaptureContext*>(ctx->move()->children[0]))
		{
			pieceSymbol = pieceSymbols[static_cast<antlr4::tree::TerminalNode *>(context->piece()->children[0])->getSymbol()->getType()];
			moveType = MoveTypeSymbols::capturing;			
			cell.row = context->square()->RANK()->getText()[0]-48;
			cell.file = context->square()->FILE()->getText()[0]-98;
			// std::cout << pieceSymbol << context->square()->RANK()->getText()[0] << cell.row << "|" << context->square()->FILE()->getText()[0]<< cell.file << std::endl;
			if(context->in_position())
				ambiguity = context->in_position()->RANK()? context->in_position()->RANK()->getText()[0] : context->in_position()->FILE()->getText()[0];
		} 
	}

	if( this->semanticAnalyzer->board.findPieceToMove(cell, pieceSymbol, moveType, ambiguity, promotionSymbol, checkState))
		printMovement(cell, pieceSymbol, moveType, ambiguity, promotionSymbol, checkState);
	else
		exit(1);

	return "Hola";
}

void chess_parseCustomVisitor::printMovement(Coordinates cell, char pieceSymbol, MoveTypeSymbols moveType, char ambiguity, char promotionSymbol, CheckStates checkState)
{
	if((this->currentMovement++ % 2) == 0)
		semanticAnalyzer->gameStream << currentMovement/2 - 1 << ". ";
	if(moveType == MoveTypeSymbols::longCastle)
	{
		semanticAnalyzer->gameStream << "0-0-0 "; 
		return;
	}
	else if (moveType == MoveTypeSymbols::shortCastle)
	{
		semanticAnalyzer->gameStream << "0-0 ";
		return;
	}

	if(pieceSymbol != 'P')
		semanticAnalyzer->gameStream << pieceSymbol;
	if(ambiguity != '\0')
		semanticAnalyzer->gameStream << ambiguity;
	if(moveType == MoveTypeSymbols::capturing || moveType == MoveTypeSymbols::capturingPromotion)
		semanticAnalyzer->gameStream << 'x';
	char fileChar = cell.file+97;
	semanticAnalyzer->gameStream << std::string(&fileChar) << cell.row;

	if(moveType == MoveTypeSymbols::promotion || moveType == MoveTypeSymbols::capturingPromotion)
	{
		semanticAnalyzer->gameStream << "=" << promotionSymbol;
	}

	semanticAnalyzer->gameStream << " ";
}


