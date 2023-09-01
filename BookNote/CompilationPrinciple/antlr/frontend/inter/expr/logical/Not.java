package inter.expr.logical;

import inter.Expr;
import inter.expr.Logical;
import lexer.Token;

public class Not extends Logical {
    public Not(Token token, Expr expr) {
        super(token, expr, expr);
    }

    @Override
    public void jumping(int t, int f) {
        expr2.jumping(t, f);
    }

    @Override
    public String toString() {
        return op.toString() + " " + expr2.toString();
    }
}
