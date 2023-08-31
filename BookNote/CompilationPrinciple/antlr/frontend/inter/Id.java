package inter;

import lexer.*;
import symbols.*;
public class Id extends Expr {
    public int offset;

    public Id (Word id, Type type, int b) {
        super(id, type);
        offset = b;
    }
}
