package src;
public enum ToeknType {
    // Group 0
    EOF, WS, UNKNOWN,

    // Group 1
    IF, ELSE, ID, INT,

    // Group 2
    EQ, NE, LT, LE, GT, GE,

    // Group 3
    REAL, SCI
}