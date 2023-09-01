package inter.expr.operator;

import inter.Expr;
import inter.expr.Id;
import inter.expr.Op;
import lexer.*;
import symbols.*;

public class Access extends Op {
    public Id array;
    public Expr index;

    public Access(Id a, Expr i, Type p) {
        super(new Word("[]", Tag.INDEX), p);
        array = a; index = i;
    }

    @Override
    public Expr gen() {
        return new Access(array, index.reduce(), type);
    }

    @Override
    public void jumping(int t, int f) {
        emitjumps(reduce().toString(), t, f);
    }

    @Override
    public String toString() {
        return array.toString() + " [ " + index.toString() + " ]";
    }
}
