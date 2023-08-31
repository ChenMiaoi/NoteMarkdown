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

    public static boolean numeric (Type type) {
        return type == Type.Char || type == Type.Int || type == Type.Float;
    }

    public static Type max (Type type1, Type type2) {
        if (!numeric(type1) || !numeric(type2))
            return null;
        else if (type1 == Type.Float || type2 == Type.Float)
            return Type.Float;
        else if (type1 == Type.Int || type2 == Type.Int)
            return Type.Int;
        else return Type.Char;
    }
}
