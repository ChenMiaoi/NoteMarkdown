package lexer;

import symbols.*;

import java.io.IOException;
import java.util.Hashtable;

/**
 * 词法分析器
 * */
public class Lexer {
    public static int line = 1;
    char peek = ' ';
    Hashtable words = new Hashtable();

    void reserve(Word w) {
        words.put(w.lexeme, w);
    }

    public Lexer() {
        reserve( new Word("if",     Tag.IF));
        reserve( new Word("else",   Tag.ELSE));
        reserve( new Word("while",  Tag.WHILE));
        reserve( new Word("do",     Tag.DO));
        reserve( new Word("break",  Tag.BREAK));
        reserve( Word.True ); reserve( Word.False );
        reserve( Type.Int  ); reserve( Type.Char  );
        reserve( Type.Bool ); reserve( Type.Float );
    }

    void readch() throws IOException {
        peek = (char) System.in.read();
    }

    boolean readch(char c) throws IOException {
        readch();
        if (peek != c)
            return false;
        peek = ' ';
        return true;
    }

    public Token scan() throws IOException {
        for (; ; readch()) {
            if (peek == ' ' || peek == '\t') continue;
            else if (peek == '\n') line = line + 1;
            else break;
        }
        switch (peek) {
            case '&' -> { // &&
                if (readch('&')) return Word.and;
                else return new Token('&');
            }
            case '|' -> { // ||
                if (readch('|')) return Word.or;
                else return new Token('|');
            }
            case '=' -> { // ==
                if (readch('=')) return Word.eq;
                else return new Token('=');
            }
            case '!' -> { // !=
                if (readch('=')) return Word.ne;
                else return new Token('!');
            }
            case '<' -> { // <=
                if (readch('=')) return Word.le;
                else return new Token('<');
            }
            case '>' -> { // >=
                if (readch('=')) return Word.ge;
                else return new Token('>');
            }
        }
        if (Character.isDigit(peek)) { // 先确定是ID还是NUM
            int v = 0;
            do {    // 不论如何，Real和Num都需要公有计算整数部分
                v = 10 * v + Character.digit(peek, 10);
                readch();
            } while (Character.isDigit(peek));

            if (peek != '.') // 如果没有小数点，就说明是整型
                return new Num(v);

            float x = v; float d = 10;
            while (true) {  // 计算小数部分，d是精度
                readch();
                if (!Character.isDigit(peek)) break;
                x = x + Character.digit(peek, 10) / d;
                d = d * 10;
            }
            return new Real(x);
        }
        if (Character.isLetter(peek)) { // ID
            StringBuffer stringBuffer = new StringBuffer();
            do {
                stringBuffer.append(peek);
                readch();
            } while (Character.isLetterOrDigit(peek));

            String s = stringBuffer.toString();
            Word word = (Word) words.get(s);    // 判断是不是保留字类型：int, float等
            if (word != null)
                return word;
            word = new Word(s, Tag.ID);
            words.put(s, word); // 将ID放入集合中
            return word;
        }

        Token token = new Token(peek);
        peek = ' ';
        return token;
    }
}
