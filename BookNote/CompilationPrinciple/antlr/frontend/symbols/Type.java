package symbols;

import lexer.*;

/**
 * 类型处理部分
 * */
public class Type extends Word {
    public static final Type
        Int     = new Type("int",   Tag.BASIC, 4),
        Float   = new Type("float", Tag.BASIC, 8),
        Char    = new Type("char",  Tag.BASIC, 1),
        Bool    = new Type("bool",  Tag.BASIC, 1);

    public int width;
    public Type (String lexeme, int tag, int width) {
        super(lexeme, tag);
        this.width = width;
    }
}
