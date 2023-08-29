lexer grammar DragonLexerRule ;

WS : [ \t\r\n]+ -> skip ;

IF : 'if' ;
ELSE : 'else' ;

ID : LETTER (LETTER | DIGIT)* ;

INT : DIGITS;

EQ : '=';
NE : '<>' ;
LT : '<' ;
LE : '<=' ;
GT : '>' ;
GE : '>=' ;

DOT : '.' ;
POS : '+' ;
NEG : '-' ;

REAL : DIGITS ('.' DIGIT)? ;
SCI : DIGIT ('.' DIGIT)? ([eE] [+-]? DIGIT)? ;

fragment DIGIT : [0-9] ;
fragment DIGITS : [0-9]+ ;
fragment LETTER : [a-zA-Z] ;