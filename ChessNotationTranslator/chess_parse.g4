grammar chess_parse;

// Lexer
WS : [ \t\r\n] -> skip ;

KNIGHT		: 'Caballo';
KING 		: 'Rey' ;
BISHOP 		: 'Alfil' ;
ROOK 		: 'Torre' ;
PAWN 		: 'Peon' ;
SHORT_CASTLING    : 'Enroque corto';
LONG_CASTLING	  : 'Enroque largo';

QUEEN 		: ('Reina' | 'Dama') ;
COMMA 		: ',' -> channel(HIDDEN);


GAME_END:   'Empate' | 'Ganan blancas' | 'Ganan negras';
IN 			: 'en' ;
FILE 		: [a-hA-H] ;
RANK 		: [1-8] ;
CAPTURES 	: 'toma' ;
PROMOTES_TO	: 'corona a';
JAQUE 		: 'jaque';
MATE		: 'mate';

// Review
//ID	 		: ([a-zA-Z_]+[a-zA-Z_0-9 ]+)?;
ID:         '"'(.*?)'"';
NUMBER:		[0-9]+;

DATE		: NUMBER '.' NUMBER '.' NUMBER;
ROUNDS		: NUMBER;


game: header play 
	  | header play GAME_END;

// Syntax
header		: ID DATE NUMBER ID ID;

play		: move
			| play move
			| play move JAQUE
			| play move MATE;

move 		: commute | capture | promotion | SHORT_CASTLING | LONG_CASTLING;

square 		: FILE RANK ;

in_position : IN RANK
			| IN FILE
			;

promotion 	: PAWN square PROMOTES_TO promotion_piece
			| PAWN CAPTURES square PROMOTES_TO promotion_piece
			| PAWN in_position CAPTURES square PROMOTES_TO promotion_piece
			| PAWN in_position PROMOTES_TO promotion_piece
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

promotion_piece	: KNIGHT
				| BISHOP
				| ROOK
				| QUEEN
				;
