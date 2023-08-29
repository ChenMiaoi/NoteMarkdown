grammar SysY ;

prog : 'prog'* EOF ;

CONST : 'const' ;
INT : 'int' ;
VOID : 'void' ;
IF : 'if' ;
ELSE : 'else' ;
WHILE : 'while' ;
BREAK : 'break';
CONTINUE : 'continue' ;
RETURN : 'return' ;
PLUS : '+' ;
MINUS : '-' ;
MUL : '*' ;
DIV : '/' ;
MOD : '%' ;
ASSIGN : '=' ;
EQ : '==' ;
NEQ : '!=' ;
LT : '<' ;
GT :'>' ;
LE : '<=' ;
GE : '>=' ;
NOT : '!' ;
AND : '&&' ;
OR : '||' ;
L_PAREN : '(' ;
R_PAREN : ')' ;
L_BRACE : '{' ;
R_BRACE : '}' ;
L_BRACKT : '[' ;
R_BRACKT : ']' ;
COMMA : ',' ;
SEMICOLON : ';' ;

IDENT : ('_' | LETTER)('_' | LETTER | DIGIT)* ;
INTEGER_CONST : OCTAL_CONST
              | HEXDECIMAL_CONST
              | DECIMAL_CONST
              ;

WS : [ \t\r\n] -> skip ;
LINE_COMMENT : '//' .*? '\n' -> skip ;
MULTILINE_COMMENT : '/*' .*? '*/' -> skip ;

fragment DIGIT : [0-9] ;
fragment LETTER : [a-zA-Z] ;
fragment DECIMAL_CONST : '0'
                       | [1-9] DIGIT* ;
fragment OCTAL_CONST : '0'[0-7]+ ;
fragment HEXDECIMAL_CONST : '0x'[a-fA-F]DIGIT+
                          | '0X'[a-fA-F]DIGIT+ ;

