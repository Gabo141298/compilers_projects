grammar chess_parse;

// Lexer
WS : [' '|'\t' | '\r' | '\n'] -> skip ;

KNIGHT		: 'Caballo';
KING 		: 'Rey' ;
BISHOP 		: 'Alfil' ;
ROOK 		: 'Torre' ;
PAWN 		: 'Peon' ;
QUEEN 		: ('Reina' | 'Dama') ;
COMMA 		: ',' -> channel(HIDDEN);

IN 			: 'en' ;
FILE 		: [a-hA-H] ;
RANK 		: [1-8] ;
CAPTURES 	: 'toma' ;

// Review
ID	 		: ([a-zA-Z_]+[a-zA-Z_0-9]+)?;

NUMBER:		[0-9]+;

DATE		: NUMBER '.' NUMBER '.' NUMBER;
ROUNDS		: NUMBER;


game: header play;

// Syntax
header		: ID DATE NUMBER ID ID;

play: move | 
	  play move;
	 
move : commute  | capture  ;

square 		: FILE RANK ;

in_position : IN RANK
			| IN FILE
			;

commute 	: piece square 
			| piece in_position square
			;

capture 	: piece CAPTURES square
			| piece in_position CAPTURES square
			;

piece 		: KNIGHT
			| KING
			| BISHOP
			| ROOK
			| PAWN
			| QUEEN
			;
