package inter.expr.operator;

import inter.Expr;
import inter.expr.Op;
import lexer.*;
import symbols.*;

public class Unary extends Op {
    public Expr expr;

    public Unary (Token token, Expr expr) {
        super(token, null);
        this.expr = expr;
        type = Type.max(Type.Int, expr.type);
        if (type == null)
            error("type error");
    }

    @Override
    public Expr gen() {
        return new Unary(op, expr.reduce());
    }

    @Override
    public String toString() {
        return op.toString() + " " + expr.toString();
    }
}
