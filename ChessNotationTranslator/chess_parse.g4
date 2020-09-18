grammar chess_parse;

// Lexer
WS : [ \t\r\n,]+ -> skip ;

KNIGHT		: 'Caballo' ;
KING 		: 'Rey' ;
BISHOP 		: 'Alfil' ;
ROOK 		: 'Torre' ;
PAWN 		: 'Peon' ;
QUEEN 		: ('Reina | Dama') ;

IN 			: 'en' ;
FILE 		: [a-hA-H] ;
RANK 		: [1-8] ;

CAPTURES 	: 'toma' ;

ID	 		: [^,]+ ;

// Syntax
square 		: FILE RANK ;

in_position : IN RANK
			| IN FILE
			;

movement 	: piece square 
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
