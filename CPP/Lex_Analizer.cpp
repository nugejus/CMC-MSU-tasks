#include <iostream>
#include <cstring>
enum type_of_lex
{
    LEX_NULL,
    LEX_PROGRAM, // program
    LEX_READ,    // read
    LEX_WRITE,   // write
    LEX_INT,     // types
    LEX_BOOL,
    LEX_TRUE, // logical value
    LEX_FALSE,
    LEX_AND, // logical ari
    LEX_OR,
    LEX_XOR,       //^
    LEX_NOT,
    LEX_DO, // repeat
    LEX_WHILE,
    LEX_FOR,
    LEX_IF, // if else
    LEX_ELSE,
    LEX_CASE,
    LEX_OF,
    LEX_END,
    LEX_ASSIGN,    //=
    LEX_PLUS,      //+
    LEX_MINUS,     //-
    LEX_SLASH,     ///
    LEX_MUL,       //*
    LEX_REM,       //%
    LEX_GTR,       //>
    LEX_LSS,       //<
    LEX_EQ,        //==
    LEX_GEQ,       //>=
    LEX_LEQ,       //<=
    LEX_NEQ,       //!=
    LEX_OBRACKET,  //(
    LEX_CBRACKET,  //)
    LEX_OBRACE,    //{
    LEX_CBRACE,    //}
    LEX_OSQBR,     //[
    LEX_CSQBR,     //]
    LEX_COMMA,     //,
    LEX_SEMICOLON, //;
    LEX_COLON,     //:
    LEX_FIN,
    LEX_NUM,
    LEX_STR,
    LEX_ID,
    POLIZ_LABEL,
    POLIZ_ADDRESS,
    POLIZ_GO,
    POLIZ_FGO
};
const char *TW[] =
    {
        "",
        "program",
        "read",
        "write",
        "int",
        "boolean",
        "true",
        "false",
        "and",
        "or",
        "not",
        "do",
        "while",
        "for",
        "if",
        "else",
        "case",
        "of",
        "end",
        NULL};
const char *TD[] =
    {
        "",
        "=",
        "+",
        "-",
        "/",
        "*",
        "%",
        ">",
        "<",
        "==",
        ">=",
        "<=",
        "!=",
        "(",
        ")",
        "{",
        "}",
        "[",
        "]",
        ",",
        ";",
        ":",
        NULL};
class Lex
{
    type_of_lex t_lex;
    int v_lex;

public:
    Lex(type_of_lex t = LEX_NULL, int v = 0)
    {
        t_lex = t;
        v_lex = v;
    }
    type_of_lex get_type() { return t_lex; }
    int get_value() { return v_lex; }
    friend std::ostream &operator<<(std::ostream &s, Lex l)
    {
        s << '(' << l.t_lex << ',' << l.v_lex << "); ";
        return s;
    }
    // friend int main(int argc, char **argv);
};

class Ident
{
    char *name;
    bool declare;
    type_of_lex type;
    bool assign;
    int value;

public:
    Ident()
    {
        declare = false;
        assign = false;
    }
    char *get_name()
    {
        return name;
    }
    void put_name(const char *n)
    {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    bool get_declare()
    {
        return declare;
    }
    void put_declare()
    {
        declare = true;
    }
    type_of_lex get_type()
    {
        return type;
    }
    void put_type(type_of_lex t)
    {
        type = t;
    }
    bool get_assign()
    {
        return assign;
    }
    void put_assign()
    {
        assign = true;
    }
    int get_value()
    {
        return value;
    }
    void put_value(int v)
    {
        value = v;
    }
};
class tabl_ident
{
    Ident *p;
    int size;
    int top;

public:
    tabl_ident(int max_size)
    {
        p = new Ident[size = max_size];
        top = 1;
    }
    ~tabl_ident()
    {
        delete[] p;
    }
    Ident &operator[](int k)
    {
        return p[k];
    }
    int put(const char *buf);
};
int tabl_ident::put(const char *buf)
{
    for (int j = 1; j < top; ++j)
        if (!strcmp(buf, p[j].get_name()))
            return j;
    p[top].put_name(buf);
    ++top;
    return top - 1;
}

tabl_ident TID(100);

class Scanner
{
    FILE *fp;
    char c;
    char buf[80];
    int buf_top;
    static type_of_lex words[];
    static type_of_lex dlms[];
    enum status
    {
        S,     // start symbol
        IDENT, // symbol
        NUMB,  // number
        COM, //{
        ALE, //:,<,>
        ER,
        DELIM,
        NEQ, //!
    };
    status CS;
    void clear()
    {
        buf_top = 0;
        for (int j = 0; j < 80; ++j)
            buf[j] = '\0';
    }
    void add()
    {
        buf[buf_top++] = c;
    }
    int look(const char *buf, const char **list)
    {
        int i = 0;
        while (list[i])
        {
            if (!strcmp(buf, list[i]))
                return i;
            ++i;
        }
        return 0;
    }
    void gc()
    {
        c = fgetc(fp);
    }

public:
    Scanner(const char *program)
    {
        fp = fopen(program, "r");
        CS = S;
        clear();
        gc();
    }
    Lex get_lex();
};
type_of_lex Scanner::words[] =
    {
        LEX_NULL,
        LEX_PROGRAM, // program
        LEX_READ,    // read
        LEX_WRITE,   // write
        LEX_INT,     // types
        LEX_BOOL,
        LEX_TRUE, // logical value
        LEX_FALSE,
        LEX_AND, // logical ari.
        LEX_OR,
        LEX_NOT,
        LEX_DO, // repeat
        LEX_WHILE,
        LEX_FOR,
        LEX_IF, // if else
        LEX_ELSE,
        LEX_CASE,
        LEX_OF,
        LEX_END,
        LEX_NULL};
type_of_lex Scanner::dlms[] =
    {
        LEX_NULL,
        LEX_ASSIGN,    //=
        LEX_PLUS,      //+
        LEX_MINUS,     //-
        LEX_SLASH,     ///
        LEX_MUL,       //*
        LEX_REM,       //%
        LEX_GTR,       //>
        LEX_LSS,       //<
        LEX_EQ,        //==
        LEX_GEQ,       //>=
        LEX_LEQ,       //<=
        LEX_NEQ,       //!=
        LEX_OBRACKET,  //(
        LEX_CBRACKET,  //)
        LEX_OBRACE,    //{
        LEX_CBRACE,    //}
        LEX_OSQBR,     //[
        LEX_CSQBR,     //]
        LEX_COMMA,     //,
        LEX_SEMICOLON, //;
        LEX_COLON,     //:
        LEX_NULL};
Lex Scanner::get_lex()
{
    int d, j;
    CS = S;
    clear();
    do
    {
        switch (CS)
        {
        case S:
            if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
                gc();
            else if (isalpha(c))
            {
                clear();
                add();
                gc();
                CS = IDENT;
            }
            else if (isdigit(c))
            {
                d = c - '0';
                gc();
                CS = NUMB;
            }
            else if (c == '/')
            {
                gc();
                if (c == '*')
                {
                    CS = COM;
                    gc();
                }
                else
                {
                    c = '/';
                    CS = DELIM;
                }
            }
            else if (c == '=' || c == '<' || c == '>')
            {
                clear();
                add();
                gc();
                CS = ALE;
            }
            else if (c == EOF)
                return Lex(LEX_FIN);
            else if (c == '!')
            {
                clear();
                add();
                gc();
                CS = NEQ;
            }
            else
                CS = DELIM;
            break;
        case IDENT:
            if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
                CS = S;
            if (isalpha(c) || isdigit(c))
            {
                add();
                gc();
            }
            else if (j = look(buf, TW))
                return Lex(words[j], j);
            else
            {
                j = TID.put(buf);
                return Lex(LEX_ID, j);
            }
            break;
        case NUMB:
            if (isdigit(c))
            {
                d = d * 10 + (c - '0');
                gc();
            }
            else
                return Lex(LEX_NUM, d);
            break;
        case COM:
            if (c == '*')
            {
                gc();
                if (c == '/')
                    CS = S;
                gc();
            }
            else if (c == EOF)
                throw c;
            else
            {
                gc();
            }
            break;
        case ALE:
            if (c == '=')
            {
                add();
                gc();
                j = look(buf, TD);
                return Lex(dlms[j], j);
            }
            else
                j = look(buf, TD);
            return Lex(dlms[j], j);
            break;
        case NEQ:
            if (c == '=')
            {
                add();
                gc();
                j = look(buf, TD);
                return Lex(LEX_NEQ, j);
            }
            else
            {
                j = look(buf, TD);
                return Lex(LEX_NOT, j);
            }
            break;
        case DELIM:
            clear();
            add();
            if (j = look(buf, TD))
            {
                gc();
                return Lex(dlms[j], j);
            }
            else
                throw c;
            break;
        } // end switch
    } while (true);
}
