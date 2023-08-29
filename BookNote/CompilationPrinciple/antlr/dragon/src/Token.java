package src;
public class Token {
    public static final Token EOF       = new Token(ToeknType.EOF, "eof");
    public static final Token WS        = new Token(ToeknType.WS, "ws");
    public static final Token UNKNOWN   = new Token(ToeknType.UNKNOWN, "unknown");
    public static final Token IF        = new Token(ToeknType.IF, "if");
    public static final Token ELSE      = new Token(ToeknType.ELSE, "else");
    public static final Token ID        = new Token(ToeknType.ID, "id");
    public static final Token INT       = new Token(ToeknType.INT, "int");
    public static final Token EQ        = new Token(ToeknType.EQ, "=");
    public static final Token NE        = new Token(ToeknType.NE, "<>");
    public static final Token LE        = new Token(ToeknType.LE, "<=");
    public static final Token LT        = new Token(ToeknType.LT, "<");
    public static final Token GE        = new Token(ToeknType.GE, ">=");
    public static final Token GT        = new Token(ToeknType.GT, ">");
    public static final Token REAL      = new Token(ToeknType.REAL, "real");
    public static final Token SCI       = new Token(ToeknType.SCI, "sci");

    private final ToeknType type;
    private final String text;

    public Token (ToeknType type, String text) {
        this.type = type;
        this.text = text;
    }

    public ToeknType getType () { return type; }
    public String getText () { return text; }

    @Override
    public String toString() {
        return "Token{" +
                "type=" + type +
                ", text='" + text + '\'' +
                '}';
    }
}