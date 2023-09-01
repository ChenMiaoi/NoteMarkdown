package inter.stmt;

import inter.Expr;
import inter.expr.Id;
import inter.Stmt;
import symbols.*;

public class Set extends Stmt {
    public Id id;
    public Expr expr;

    public Set(Id i, Expr x) {
        id = i;
        expr = x;

        if (check(id.type, expr.type) == null)
            error("type error");
    }

    public Type check(Type type1, Type type2) {
        if (Type.numeric(type1) && Type.numeric(type2))
            return type2;
        else if (type1 == Type.Bool && type2 == Type.Bool)
            return type2;
        else return null;
    }

    @Override
    public void gen(int b, int a) {
        emit(id.toString() + " = " + expr.gen().toString());
    }
}
