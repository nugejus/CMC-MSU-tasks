/*V2.0
1. case-of operation(only 1 var can be in case; only 1 parameter)*/

#include <iostream>
#include "Lex_Analizer.cpp"
template <class T, int max_size>
class Stack
{
    T s[max_size];
    int top;

public:
    Stack() { top = 0; }
    void reset() { top = 0; }
    void push(T i);
    T pop();
    bool is_empty() { return top == 0; }
    bool is_full() { return top == max_size; }
    void check_val(int v)
    {
        for (int i = 0; i < top; i++)
        {
            if (s[i] == v)
                throw "already exist value";
        }
    }
    void print_s()
    {
        for (int i = 0; i < top; i++)
            std::cout << s[i] << " ";
        std::cout << ";";
    }
};

template <class T, int max_size>
void Stack<T, max_size>::push(T i)
{
    if (!is_full())
    {
        s[top] = i;
        ++top;
    }
    else
        throw "Stack over flow";
}
template <class T, int max_size>
T Stack<T, max_size>::pop()
{
    if (!is_empty())
    {
        --top;
        return s[top];
    }
    else
        throw "Stack_is_empty";
}

class Poliz
{
    Lex *p;
    int size;
    int free;

public:
    Poliz(int max_size)
    {
        p = new Lex[size = max_size];
        free = 0;
    };
    ~Poliz() { delete[] p; };
    void put_lex(Lex l)
    {
        p[free] = l;
        ++free;
    };
    void put_lex(Lex l, int place) { p[place] = l; };
    void blank() { ++free; };
    int get_free() { return free; };
    Lex &operator[](int index)
    {
        if (index > size)
            throw "POLIZ:out of array";
        else if (index > free)
            throw "POLIZ:indefinite element of array";
        else
            return p[index];
    };
    void print()
    {
        std::cout << "\n";
        for (int i = 0; i < free; ++i)
            std::cout << p[i];
        std::cout << "\n";
    };
};

class Parser
{
    Lex curr_lex;
    type_of_lex c_type;
    int c_val;
    Scanner scan;
    Stack<int, 100> st_int;
    Stack<type_of_lex, 100> st_lex;
    void P(); // процедуры РС-метода
    void D1();
    void D2();
    void D();
    void B();
    void S();
    void E();
    void E1();
    void T();
    void F();
    void dec(type_of_lex type); // семантичиеские действия
    void check_id();
    void check_op();
    void check_not();
    void eq_type();
    void eq_bool();
    void check_id_in_read();
    void gl() // получить очередную лексему
    {
        curr_lex = scan.get_lex();
        c_type = curr_lex.get_type();
        c_val = curr_lex.get_value();
    }

public:
    Poliz prog; // внутреннее представление программы
    Parser(const char *program) : scan(program), prog(1000) {}
    void analyze(); // анализатор с действиями
};
void Parser::dec(type_of_lex type)
{
    int i;
    while (!st_int.is_empty())
    {
        i = st_int.pop();
        if (TID[i].get_declare())
            throw "twice";
        else
        {
            TID[i].put_declare();
            TID[i].put_type(type);
        }
    }
}
void Parser::check_id()
{
    if (TID[c_val].get_declare())
        st_lex.push(TID[c_val].get_type());
    else
    {
        throw "not declared";
    }
}
void Parser::check_op()
{
    type_of_lex t1, t2, op, t = LEX_INT, r = LEX_BOOL;
    t2 = st_lex.pop();
    op = st_lex.pop();
    t1 = st_lex.pop();
    if (op == LEX_PLUS || op == LEX_MINUS || op == LEX_MUL || op == LEX_SLASH || op == LEX_REM)
        r = LEX_INT;
    if (op == LEX_OR || op == LEX_AND)
        t = LEX_BOOL;
    if (t1 == t2 && t1 == t)
        st_lex.push(r);
    else
        throw "wrong types are in operation";
}
void Parser::check_not()
{
    if (st_lex.pop() != LEX_BOOL)
        throw "wrong type is in not";
    else
    {
        st_lex.push(LEX_BOOL);
    }
}
void Parser::eq_type()
{
    if (st_lex.pop() != st_lex.pop())
        throw "wrong types are in :=";
}

void Parser::analyze()
{
    using namespace std;
    gl();
    P();
}
void Parser::eq_bool()
{
    if (st_lex.pop() != LEX_BOOL)
        throw "expression is not boolean";
}
void Parser::check_id_in_read()
{
    if (!TID[c_val].get_declare())
        throw "not declared";
}
void Parser::P()
{
    if (c_type == LEX_PROGRAM)
        gl();
    else
        throw curr_lex;
    if (c_type != LEX_OBRACE)
        throw curr_lex;
    gl();
    if (c_type == LEX_CBRACE)
        return;
    D();
    B();
    if (c_type != LEX_FIN)
        throw curr_lex;
}
void Parser::D()
{
    st_int.reset();
    do
    {
        if (c_type == LEX_INT)
        {
            gl();
            D1();
        }
        else if (c_type == LEX_BOOL)
        {
            gl();
            D2();
        }
        else
            return;
        gl();
    } while (c_type == LEX_INT || c_type == LEX_BOOL);
}
void Parser::D1()
{
    if (c_type != LEX_ID)
        throw curr_lex;
    else
    {
        st_int.push(c_val);
        gl();
        while (c_type == LEX_COMMA)
        {
            gl();
            if (c_type != LEX_ID)
                throw curr_lex;
            else
            {
                st_int.push(c_val);
                gl();
            }
        }
    }
    if (c_type != LEX_SEMICOLON)
        throw curr_lex;
    else
        dec(LEX_INT);
}
void Parser::D2()
{
    if (c_type != LEX_ID)
        throw curr_lex;
    else
    {
        st_int.push(c_val);
        gl();
        while (c_type == LEX_COMMA)
        {
            gl();
            if (c_type != LEX_ID)
                throw curr_lex;
            else
            {
                st_int.push(c_val);
                gl();
            }
        }
    }
    if (c_type != LEX_SEMICOLON)
        throw curr_lex;
    else
        dec(LEX_BOOL);
}
void Parser::B()
{
    S();
    while (c_type == LEX_SEMICOLON)
    {
        gl();
        S();
    }
    if (c_type == LEX_CBRACE)
        gl();
    else
        throw curr_lex;
}
void Parser::S()
{
    int pl0, pl1, pl2, pl3;
    if (c_type == LEX_IF)
    {
        gl();
        E();
        eq_bool();
        pl2 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_FGO));
        if (c_type == LEX_OBRACE)
        {
            gl();
            B();
            pl3 = prog.get_free();
            prog.blank();
            prog.put_lex(Lex(POLIZ_GO));
            prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl2);
            if (c_type == LEX_ELSE)
            {
                gl();
                if (c_type != LEX_OBRACE)
                    throw curr_lex;
                gl();
                B();
                prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl3);
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    } // end if

    else if (c_type == LEX_DO)
    {
        gl();
        if (c_type != LEX_OBRACE)
            throw curr_lex;
        pl1 = prog.get_free(); // jump go
        gl();
        B();
        if (c_type != LEX_WHILE)
            throw curr_lex;
        gl();
        if (c_type != LEX_OBRACKET)
            throw curr_lex;
        E();
        eq_bool();
        if (c_type != LEX_SEMICOLON)
            throw curr_lex;
        pl0 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_FGO));
        prog.put_lex(Lex(POLIZ_LABEL, pl1));
        prog.put_lex(Lex(POLIZ_GO));
        prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl0);
    } // end do-while

    else if (c_type == LEX_FOR)
    {
        gl();
        if (c_type != LEX_OBRACKET)
            throw curr_lex;
        gl();
        if (c_type != LEX_ID)
            throw curr_lex;
        S();
        if (c_type != LEX_SEMICOLON)
            throw curr_lex;
        pl0 = prog.get_free(); // jump go
        gl();
        E();
        eq_bool();
        pl1 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_FGO));
        if (c_type != LEX_SEMICOLON)
            throw curr_lex;
        gl();
        if (c_type != LEX_ID)
            throw curr_lex;
        S();
        if (c_type != LEX_CBRACKET)
            throw curr_lex;
        gl();
        if (c_type != LEX_OBRACE)
            throw curr_lex;
        gl();
        B();
        prog.put_lex(Lex(POLIZ_LABEL, pl0));
        prog.put_lex(Lex(POLIZ_GO));
        prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl1);
    } // end for

    if (c_type == LEX_CASE)
    {
        Lex x;
        int pl[100], ind = 0;
        st_int.reset();
        gl();
        x = curr_lex;
        check_id();
        gl();
        if (c_type != LEX_OF)
            throw curr_lex;
        do
        {
            gl();
            if (c_type == LEX_END)
            {
                gl();
                break;
            }
            if (c_type != LEX_NUM)
                throw curr_lex;
            prog.put_lex(Lex(LEX_ID, x.get_value()));
            st_int.check_val(c_val);
            st_int.push(c_val);
            st_lex.push(LEX_INT);
            prog.put_lex(curr_lex);
            prog.put_lex(Lex(LEX_EQ));
            pl0 = prog.get_free();
            prog.blank();
            prog.put_lex(Lex(POLIZ_FGO));
            gl();
            if (c_type == LEX_COLON)
            {
                gl();
                S();
                // gl();
            }
            else
                throw curr_lex;
            if (c_type != LEX_SEMICOLON)
                throw curr_lex;
            pl[ind] = prog.get_free();
            ind++;
            prog.blank();
            prog.put_lex(Lex(POLIZ_GO));
            prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl0);
        } while (c_type != LEX_END);
        for (int i = 0; i < ind; i++)
        {
            prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl[i]);
        }
        prog.put_lex(LEX_END);
    } // case

    else if (c_type == LEX_READ)
    {
        gl();
        if (c_type == LEX_OBRACKET)
        {
            gl();
            if (c_type == LEX_ID)
            {
                check_id_in_read();
                prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
                gl();
            }
            else
                throw curr_lex;
            if (c_type == LEX_CBRACKET)
            {
                gl();
                prog.put_lex(Lex(LEX_READ));
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    } // end read
    else if (c_type == LEX_WRITE)
    {
        gl();
        if (c_type != LEX_OBRACKET)
            throw curr_lex;
        else
        {
            gl();
            E();
            if (c_type == LEX_CBRACKET)
            {
                gl();
                prog.put_lex(Lex(LEX_WRITE));
            }
            else
                throw curr_lex;
        }
    } // end write
    else if (c_type == LEX_ID)
    {
        check_id();
        prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
        gl();
        if (c_type == LEX_ASSIGN)
        {
            gl();
            E();
            eq_type();
            prog.put_lex(Lex(LEX_ASSIGN));
        }
        else
            throw curr_lex;
    } // assign-end
    else
        return;
}
void Parser::E()
{
    type_of_lex x;
    E1();
    x = c_type;
    if (c_type == LEX_EQ || c_type == LEX_LSS || c_type == LEX_GTR ||
        c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ)
    {
        st_lex.push(c_type);
        gl();
        E1();
        check_op();
        prog.put_lex(x);
    }
}
void Parser::E1()
{
    T();
    while (c_type == LEX_PLUS || c_type == LEX_MINUS || c_type == LEX_OR)
    {
        type_of_lex x = c_type;
        st_lex.push(c_type);
        gl();
        T();
        check_op();
        prog.put_lex(x);
    }
}
void Parser::T()
{
    F();
    while (c_type == LEX_MUL || c_type == LEX_SLASH || c_type == LEX_REM || c_type == LEX_AND)
    {
        type_of_lex x = c_type;
        st_lex.push(c_type);
        gl();
        F();
        check_op();
        prog.put_lex(x);
    }
}
void Parser::F()
{
    if (c_type == LEX_ID)
    {
        check_id();
        prog.put_lex(Lex(LEX_ID, c_val));
        gl();
    }
    else if (c_type == LEX_NUM)
    {
        st_lex.push(LEX_INT);
        prog.put_lex(curr_lex);
        gl();
    }
    else if (c_type == LEX_TRUE)
    {
        st_lex.push(LEX_BOOL);
        prog.put_lex(Lex(LEX_TRUE, 1));
        gl();
    }
    else if (c_type == LEX_FALSE)
    {
        st_lex.push(LEX_BOOL);
        prog.put_lex(Lex(LEX_FALSE, 0));
        gl();
    }
    else if (c_type == LEX_NOT)
    {
        gl();
        F();
        check_not();
    }
    else if (c_type == LEX_OBRACKET)
    {
        gl();
        E();
        if (c_type == LEX_CBRACKET)
            gl();
        else
            throw curr_lex;
    }
    else
        throw curr_lex;
}

class Executer
{
    Lex pc_el;

public:
    void execute(Poliz &prog);
};
void Executer::execute(Poliz &prog)
{
    using namespace std;
    Stack<int, 100> args;
    int i, j, index = 0, size = prog.get_free();
    bool cs = false;
    while (index < size)
    {
        pc_el = prog[index];
        switch (pc_el.get_type())
        {
        case LEX_TRUE:
        case LEX_FALSE:
        case LEX_NUM:
        case POLIZ_ADDRESS:
        case POLIZ_LABEL:
            args.push(pc_el.get_value());
            break;
        case LEX_ID:
            i = pc_el.get_value();
            if (TID[i].get_assign())
            {
                args.push(TID[i].get_value());
                break;
            }
            else
                throw "POLIZ: indefinite identifier";
        case LEX_NOT:
            args.push(!args.pop());
            break;
        case LEX_OR:
            i = args.pop();
            args.push(args.pop() || i);
            break;
        case LEX_AND:
            i = args.pop();
            args.push(args.pop() && i);
            break;
        case POLIZ_GO:
            index = args.pop() - 1;
            break;
        case POLIZ_FGO:
            i = args.pop();
            if (!args.pop())
                index = i - 1;
            break;
        case LEX_WRITE:
            cout << args.pop() << endl;
            break;
        case LEX_READ:
        {
            int k;
            i = args.pop();
            if (TID[i].get_type() == LEX_INT)
            {
                cin >> k;
            }
            else
            {
                char j[20];
            rep:
                cin >> j;
                if (!strcmp(j, "true"))
                    k = 1;
                else if (!strcmp(j, "false"))
                    k = 0;
                else
                {
                    cout << "Error in input:true/false";
                    cout << endl;
                    goto rep;
                }
            }
            TID[i].put_value(k);
            TID[i].put_assign();
            break;
        }
        case LEX_END:
            if (cs == false)
                throw "no matching value";
            break;
        case LEX_PLUS:
            args.push(args.pop() + args.pop());
            break;
        case LEX_MUL:
            args.push(args.pop() * args.pop());
            break;
        case LEX_MINUS:
            i = args.pop();
            args.push(args.pop() - i);
            break;
        case LEX_SLASH:
            i = args.pop();
            if (i)
            {
                args.push(args.pop() / i);
                break;
            }
            else
                throw "POLIZ:divide by zero";
        case LEX_REM:
            i = args.pop();
            if (i)
            {
                args.push(args.pop() % i);
                break;
            }
            else
                throw "POLIZ:divide by zero";
        case LEX_EQ:
            cs = (args.pop() == args.pop());
            args.push(cs);
            break;
        case LEX_LSS:
            i = args.pop();
            args.push(args.pop() < i);
            break;
        case LEX_GTR:
            i = args.pop();
            args.push(args.pop() > i);
            break;
        case LEX_LEQ:
            i = args.pop();
            args.push(args.pop() <= i);
            break;
        case LEX_GEQ:
            i = args.pop();
            args.push(args.pop() >= i);
            break;
        case LEX_NEQ:
            i = args.pop();
            args.push(args.pop() != i);
            break;
        case LEX_ASSIGN:
            i = args.pop();
            j = args.pop();
            TID[j].put_value(i);
            TID[j].put_assign();
            break;
        default:
            throw "POLIZ: unexpected elem";
        } // end of switch
        ++index;
    }; // end of while
}
class Interpretator
{
    Parser pars;
    Executer E;

public:
    Interpretator(const char *program) : pars(program){};
    void interpretation();
};
void Interpretator::interpretation()
{
    pars.analyze();
    pars.prog.print();
    E.execute(pars.prog);
}

int main()
{
    using namespace std;
    try
    {
        Interpretator I("do while test.txt");
        I.interpretation();
        return 0;
    }
    catch (char c)
    {
        cout << "unexpected symbol " << c << endl;
        return 1;
    }
    catch (Lex l)
    {
        cout << "unexpected lexeme";
        cout << l;
        return 1;
    }
    catch (const char *source)
    {
        cout << source << endl;
        return 1;
    }
}