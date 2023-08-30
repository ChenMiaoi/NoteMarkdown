package lexer;

/**
 * 实数类型处理部分
 * */
public class Real extends Token {
    public final float value;
    public Real (float value) {
        super(Tag.REAL);
        this.value = value;
    }

    @Override
    public String toString() {
        return "Real{\n\t" +
                "value = " + value + "\n" +
                '}';
    }
}
