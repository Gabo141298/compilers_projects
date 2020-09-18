# Chess Notation Translator
Chess is a game that has been around for over a thousand years and is well known worldwide. Given the popularity and age of this game, a way was sought in which the movements could be represented in written form, clearly and efficiently, so that players in the future, or in different countries, could know exactly how a game proceeded. departure. It was this that led to the creation of the algebraic chess notation, which uses letters, numbers and other special symbols to denote the different movements, whether they are captures, checks, checkmate, among others.

This project is a translator that receives chess moves in a file and converts it to PGN format (Portable Game Notation), which is the format used by online chess engines and boards. The project will have a lexical analyzer, which checks for correctness in the symbols of chess moves, a parser, which checks the correct order in the grammar of a chess game, and a semantic analyzer, which will have the logic of a chessboard, following the moves to verify that they are all valid.

## Input file
The system input is a text file that has the first 5 fields defined, separated by commas: name of the tournament, date of the game, round of the tournament, name of the player with white pieces and name of the player with black pieces. After this there are a variable number of fields with all the movements of the game, also separated by commas. After the last move of the game the result is indicated. It is denoted ``White wins`` to indicate that the white pieces won. ``Black win`` is used to indicate that the black pieces won. In case of a tie, write ``Tie``. The result of the game is optional, as it is possible to use a file from an unfinished game.


## Notes

This is a project for the Compilers course of Computer Science in the UCR (Universidad de Costa Rica). As such, it will have two evaluations, which will consist on the following milestones:
- **First milestone:** there will be a complete lexical analyzer and a parser that analyzes the basic chess moves. These movements will be: Pawn moving forward, bishops diagonally, rooks vertically and horizontally, queen in all of the above, knight in an L shape, king to any immediate neighboring square, as well as the captures of these pieces. The moves that will be left for the final delivery are the most advanced, such as short castling, long castling, and pawn promotions.

In this installment the semantic analysis implementation will also begin. The semantic analysis consists of creating a matrix with the starting position of a chess game. For each movement that is read from the file, after making the lexical and syntactic analysis, the movement will be taken and it will be verified that it is valid in the current board position. If so, the board will be updated to represent the new position with the last move. For the intermediate stage, the verifications will be limited to checking that the piece mentioned in the move is actually in that position on the board, and that the proposed move adjusts to the natural movement of that piece according to the rules of chess.


- **Second milestone:** The advanced movements will be implemented, such as castling and promotions.

## Versioning

We use [Github](http://github.com/) for versioning. For the versions available, see the [tags on this repository](https://github.com/jackalvarez/ChessNotationTranslator).

## Authors

* **Jostin Alvarez** - *Semantical analysis* - [jackalvarez](https://github.com/jackalvarez)

* **Gabriel Galvez** - *Lexical analysis* - [Gabo141298](https://github.com/Gabo141298)

* **Christian Rodriguez** - *Sintactic analysis* - [Gabo141298](https://github.com/ChristianRod21)

* **Bryan Ulate** - *Fixes the latex document* - [Gabo141298](https://github.com/Bulatec)

See also the list of [contributors](https://github.com/jackalvarez/AtomicAntiChess/settings/collaboration) who participated in this project.

## Acknowledgments

* PhD. Luis Quesada and PhD. Adrian Lara for providing help with the lexical and sintactic analysis
* Professor Maureen Murillo for helping with the decision taking process of the project
