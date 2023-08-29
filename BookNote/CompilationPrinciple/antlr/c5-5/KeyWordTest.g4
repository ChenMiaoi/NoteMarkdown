grammar KeyWordTest ;

prog : stat* EOF ;

stat : expr ';'
     | ID '=' expr
     | 'if' expr '{' .*? '}'
     | 'while' expr '{' .*? '}'
     ;

expr : expr ('*' | '/') expr
     | expr ('+' | '-') expr
     | '(' expr ')'
     | ID
     | INT
     | FLOAT
     | STRING
     ;

FOR : 'for' ;

STRING : '"' (ESC|.)*? '"' ;
ID : (LETTER | '_')(LETTER | DIGIT | '_')* ;
INT : '0' | [1-9]DIGIT* ;
FLOAT : DIGIT+ '.' DIGIT*
      | '.' DIGIT+
      ;

LINE_COMMENT : '//' .*? '\n' -> skip ;
DOC_COMMENT : '/**' .*? '*/' -> skip ;
ML_COMMENT : '/*' .*? '*/'  -> skip ;
WS : [ \t\r\n]+ -> skip ;

fragment DIGIT : [0-9] ;
fragment LETTER : [a-zA-Z] ;
fragment ESC : '\\"' | '\\\\' ;