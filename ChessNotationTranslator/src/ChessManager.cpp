#include "ChessManager.h"
#include <iostream>

ChessManager::ChessManager()
    : turn { 0 }
{
}

void ChessManager::setGameState()
{
    if ( false ) // Implemment stalemate or 50 move rule or three fold repetition
    {
        gameState = 'T';
    }
    else if ( false ) // Here we have to calculate that there was a checkmate by white, that is, the black king is attacked and cannot defend
    {
        gameState = 'W';
    }
    else if ( false ) // Here it is the same but for black instead of white
    {
        gameState = 'B';
    }
    else
    {
        gameState = '-'; // This is the normal state of the game, it has not finished.
    }
}

char ChessManager::getGameState() const
{
    return this->gameState;
}

int ChessManager::getTurn()
{
    return this->turn;
}
