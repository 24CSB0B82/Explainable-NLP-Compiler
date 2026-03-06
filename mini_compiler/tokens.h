// Token identification file
// Includes 5 different types of tokens
// keywords designed for mini compiler 

enum keywords {
    INT = 100,
    LONG,
    LONG_LONG,
    SHORT,
    SIGNED,
    UNSIGNED,
    CHAR,
    IF,
    ELSE,
    FOR,
    BREAK,
    CONTINUE,
    RETURN
};

enum operators {
    INCREMENT = 200,
    DECREMENT,
    PTR_SELECT,
    LOGICAL_AND,
    LOGICAL_OR,
    EQ,
    NOT_EQ,
    LS_THAN_EQ,
    GR_THAN_EQ,
    ASSIGN,
    PLUS,
    MINUS,
    STAR,
    MODULO,
    LS_THAN,
    GR_THAN
};

enum special_symbols {
    DELIMITER = 300,
    COMMA,
    FW_SLASH,
    OPEN_PAR,
    CLOSE_PAR,
    OPEN_BRACES,
    CLOSE_BRACES,
    OPEN_SQ_BRACES,
    CLOSE_SQ_BRACES,
};

enum constants {
    HEX_CONSTANT = 400,
    DEC_CONSTANT,
    HEADER_FILE,
    STRING
};

enum identifier {
    IDENTIFIER = 500
};