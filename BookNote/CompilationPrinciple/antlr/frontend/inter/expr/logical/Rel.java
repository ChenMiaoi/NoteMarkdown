package inter.expr.logical;

import inter.*;
import inter.expr.*;
import lexer.*;
import symbols.*;

public class Rel extends Logical {
    public Rel(Token token, Expr expr1, Expr expr2) {
        super(token, expr1, expr2);
    }

    @Override
    public Type check(Type type1, Type type2) {
        if (type1 instanceof Array || type2 instanceof Array) return null;
        else if (type1 == type2) return Type.Bool;
        else return null;
    }

    @Override
    public void jumping(int t, int f) {
        Expr a = expr1.reduce();
        Expr b = expr2.reduce();

        String test = a.toString() + " " + op.toString() + " " + b.toString();
        emitjumps(test, t, f);
    }
}
