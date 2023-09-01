package inter;

public class Stmt extends Node {
    public int after = 0;
    public static Stmt Null = new Stmt();
    public static Stmt Enclosing = Stmt.Null;

    public void gen(int b, int a) {}
}
