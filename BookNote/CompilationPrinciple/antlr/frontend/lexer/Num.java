package lexer;

/**
 * 整型处理部分
 * */
public class Num extends Token {
    public final int value;
    public Num (int value) {
        super(Tag.NUM);
        this.value = value;
    }

    @Override
    public String toString() {
        return "Num{\n\t" +
                "value = " + value + "\n" +
                '}';
    }
}
