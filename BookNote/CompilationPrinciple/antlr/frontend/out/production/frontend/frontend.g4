grammar frontend ;
/*
    stmt -> loc = bool;
        | if (bool) stmt
        | if (bool) stmt else stmt
        | while (bool) stmt
        | do stmt while (bool) ;
        | break ;
        | block
    loc -> loc [bool] | id

    bool -> bool || join | join
    join -> join && equality | equality
    equality -> equality == rel | equality != rel | rel
    rel -> expr < expr
        | expr <= expr
        | expr >= expr
        | expr > expr
        | expr
    expr -> expr + tern | expr - tern | tern
    tern -> tern * unary | tern / unary | unary
    unary -> ! unary | - unary | factor
    factor -> (bool) | loc | num | real | true | false
*/

stmt : loc '=' bool ';'
    | 'if' '(' bool ')' stmt
    | 'if' '(' bool ')' stmt 'else' stmt
    | 'while' '(' bool ')' stmt
    | 'do' stmt 'while' '(' stmt ')' ';'
    | 'break' ';'
    | block
    ;

loc : loc '[' bool ']'
    | ID
    ;

bool : bool '||' join
    | join
    ;

join : join '&&' equality
    | equality
    ;

equality : equality '==' rel
    | equality '!=' rel
    | rel
    ;

rel : expr '<' expr
    | expr '<=' expr
    | expr '>=' expr
    | expr '>' expr
    | expr
    ;

expr : expr '+' term
    | expr '-' term
    | term
    ;

term : term '*' unary
    | term '/' unary
    | unary
    ;

unary : '!' unary
    | '-' unary
    | factor
    ;

factor : '(' bool ')'
    | loc
    | NUM
    | REAL
    | 'true'
    | 'false'
    ;

block : '{' stmt* '}' ;

ID   : [_a-zA-Z][_a-zA-Z0-9]* ;
NUM  : [0-9]+ ;
REAL : [0-9]+ '.' [0-9]*
    | '.' [0-9]+
    ;

WS   : [ \t\r\n] -> skip ;