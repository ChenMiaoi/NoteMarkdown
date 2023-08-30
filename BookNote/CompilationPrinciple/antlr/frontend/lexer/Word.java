package lexer;

/**
 * 用于处理关系运算、bool、转跳等
 * */
public class Word extends Token {
    public static final Word
        and = new Word("&&", Tag.AND), or = new Word("||", Tag.OR),
        eq  = new Word("==", Tag.EQ),  ne = new Word("!=", Tag.NE),
        le  = new Word("<=", Tag.LE),  ge = new Word(">=", Tag.GE),
        minus   = new Word("minus", Tag.MINUS),
        True    = new Word("true",  Tag.TRUE),
        False   = new Word("false", Tag.FALSE),
        temp    = new Word("t",     Tag.TEMP);

    public String lexeme;
    public Word (String lexeme, int tag) {
        super(tag);
        this.lexeme = lexeme;
    }

    @Override
    public String toString() {
        return "Word{\n\t" +
                "lexeme = '" + lexeme + '\'' + "\n" +
                '}';
    }
}
