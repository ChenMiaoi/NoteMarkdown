package inter.stmt;

import inter.Expr;
import inter.Stmt;
import symbols.Type;

public class While extends Stmt {
    Expr expr;
    Stmt stmt;

    public While() {
        expr = null;
        stmt = null;
    }

    public void init(Expr expr, Stmt stmt) {
        this.expr = expr;
        this.stmt = stmt;

        if (this.expr.type != Type.Bool)
            this.expr.error("boolean required in while");
    }

    @Override
    public void gen(int b, int a) {
        after = a;
        expr.jumping(0, a);
        int label = newlabel();
        emitlabel(label);
        stmt.gen(label, b);
        emit("goto L" + b);
    }
}
