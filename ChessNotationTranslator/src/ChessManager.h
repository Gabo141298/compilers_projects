#ifndef CHESSMANAGER_H
#define CHESSMANAGER_H

class ChessManager
{
  private:
    /// Keeps count of the current turn of the match.
    int turn;
    /// Stores the current state of the game. '-'  = still playing, 'W' = white won, 'B' = black won.
    char gameState;


  public:
    ChessManager();
    /// It returns the current turn.
    inline int getCurrentTurn() const { return turn; }
    /// The game ended if one of the players got mated, if repetition 
    /// happenned or if there was a stalemate
    void setGameState();
    /// Return the current state of the game ('B', 'W', 'T' or '-')
    char getGameState() const;
    /// Called if a capture was made. Resets the counter of moves of that player
    void resetMovesCounter();
    /// Changes the current turn, if it is white, make it black and viceversa
    inline void changeTurn() { turn = (turn) ? 0 : 1; }
    /// Returns the current turn of the game
    int getTurn();
    /// Passes to the next turn.
    inline int operator++() { return ++turn; }
};

#endif // CHESSMANAGER_H