package inter.stmt;

import inter.Expr;
import inter.Stmt;
import symbols.*;

public class Do extends Stmt {
    Expr expr;
    Stmt stmt;

    public Do() {
        expr = null;
        stmt = null;
    }

    public void init(Stmt s, Expr x) {
        expr = x;
        stmt = s;

        if (expr.type != Type.Bool)
            expr.error("boolean required in do");
    }

    @Override
    public void gen(int b, int a) {
        after = a;
        int label = newlabel();
        stmt.gen(b, label);
        emitlabel(label);
        expr.jumping(b, 0);
    }
}
