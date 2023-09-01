package inter.expr;

import inter.Expr;
import lexer.*;
import symbols.*;

public class Constant extends Expr {
    public static final Constant
        True   = new Constant(Word.True,  Type.Bool),
        False  = new Constant(Word.False, Type.Bool);
    public Constant(Token token, Type type) {
        super(token, type);
    }
    public Constant(int i) {
        super(new Num(i), Type.Int);
    }

    @Override
    public void jumping(int t, int f) {
        if (this == True && t != 0)
            emit("goto L" + t);
        else if (this == False && f != 0)
            emit("goto L" + f);
    }
}
