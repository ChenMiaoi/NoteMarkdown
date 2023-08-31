package inter;

import lexer.*;
public class Node {
    int lexline = 0;
    static int labels = 0;

    Node () {
        lexline = Lexer.line;
    }

    void error (String str) {
        throw new Error("near line " + lexline + ": " + str);
    }
    public int newlabel() { return ++labels; }
    public void emitlabel(int i) {
        System.out.println("L" + i + ":");
    }
    public void emit(String str) {
        System.out.println("\t" + str);
    }
}
