import lexer.*;
import symbols.*;

import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        Lexer lexer = new Lexer();
        System.out.println(lexer.scan());
    }
}
