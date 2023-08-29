package src;

public class DragonLexer extends Lexer {

    public DragonLexer(String input) {
        super(input);
    }

    @Override
    public Token nextToken() {

        Token unknown = new Token(ToeknType.UNKNOWN, "unknown");
        return unknown;
    }
}
