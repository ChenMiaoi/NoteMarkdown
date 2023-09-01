package symbols;

import inter.expr.Id;
import lexer.*;

import java.util.Hashtable;

/**
 * 简易的符号表
 * <p>符号表中存储了对应的ID和词法单元，然后支持向上递归嵌套的符号表结构<p/>
 * */

public class Env {
    private Hashtable table;
    protected Env prev;

    public Env (Env env) {
        this.table = new Hashtable();
        prev = env;
    }
    public void put (Token w, Id i) {
        table.put(w, i);
    }

    public Id get (Token w) {
        for (Env env = this; env != null; env = env.prev) {
            Id found = (Id) (env.table.get(w));
            if (found != null)
                return found;
        }
        return null;
    }
}
