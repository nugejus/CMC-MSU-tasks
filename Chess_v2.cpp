/*v2.3 update log
1. Bug fix*/

#include <iostream>
using namespace std;
bool turn = false; // 0-black,1-white
class ChessPiece
{
public:
    char Color;
    char Type;
    string name;

    ChessPiece(string name1 = "None", char type1 = '-', char Color1 = 'N')
    {
        Color = Color1;
        Type = type1;
        name = name1;
    }
};
class ChessBoard
{
public:
    ChessPiece *Board[8][8];
    friend void PrintMap(ChessBoard Board);
    ChessBoard()
    {
        SetPieces();
        try
        { // White Royals
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 2; j++)
                    if (Board[j][i] == NULL)
                        throw("Incorrect Setup");
                for (int j = 6; j < 8; j++)
                    if (Board[j][i] == NULL)
                        throw("Incorrect Setup");
            }
            if (Board[0][3]->name != "King" && Board[0][3]->Color != 'w' || Board[7][4]->name != "King" && Board[7][4]->Color != 'w')
                throw("King is located not correctely");
            if (Board[0][4]->name != "Queen" && Board[0][4]->Color != 'w' || Board[7][3]->name != "Queen" && Board[7][3]->Color != 'w')
                throw("Queen is located not correctely");
            if (Board[0][2]->name != "Bishop" && Board[0][2]->Color != 'w' || Board[7][5]->name != "Bishop" && Board[7][5]->Color != 'w')
                throw("Bishop is located not correctely");
            if (Board[0][1]->name != "Knight" && Board[0][1]->Color != 'w' || Board[7][6]->name != "Knight" && Board[7][6]->Color != 'w')
                throw("Knight is located not correctely");
            if (Board[0][0]->name != "Rook" && Board[0][0]->Color != 'w' || Board[7][0]->name != "Rook" && Board[7][0]->Color != 'w')
                throw("Rook is located not correctely"); // Black Royals
            if (Board[0][2]->name != "Bishop" && Board[0][2]->Color != 'b' || Board[7][5]->name != "Bishop" && Board[7][5]->Color != 'b')
                throw("Bishop is located not correctely");
            if (Board[0][1]->name != "Knight" && Board[0][1]->Color != 'b' || Board[7][6]->name != "Knight" && Board[7][6]->Color != 'b')
                throw("Knight is located not correctely");
            if (Board[0][0]->name != "Rook" && Board[0][0]->Color != 'b' || Board[7][0]->name != "Rook" && Board[7][0]->Color != 'b')
                throw("Rook is located not correctely");
            for (int j = 0; j < 8; j++) // Pawn
                if (Board[1][j]->name != "Pawn" && Board[1][j]->Color != 'w' || Board[6][j]->name != "Pawn" && Board[6][j]->Color != 'b')
                    throw("Pawn is located not correctely");
        }
        catch (const char *x)
        {
            cout << x << "\n";
            exit(0);
        }
        PrintMap();
    }

    void SetPieces()
    {
        // Empty Space
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                Board[i][j] = NULL;
        }
        // White Royals
        Board[0][3] = new ChessPiece("King", 'K', 'w');
        Board[0][4] = new ChessPiece("Queen", 'Q', 'w');
        Board[0][0] = new ChessPiece("Rook", 'R', 'w');
        Board[0][7] = new ChessPiece("Rook", 'R', 'w');
        Board[0][1] = new ChessPiece("Knight", 'N', 'w');
        Board[0][6] = new ChessPiece("Knight", 'N', 'w');
        Board[0][5] = new ChessPiece("Bishop", 'B', 'w');
        Board[0][2] = new ChessPiece("Bishop", 'B', 'w');
        // Black Royals
        Board[7][4] = new ChessPiece("King", 'K', 'b');
        Board[7][3] = new ChessPiece("Queen", 'Q', 'b');
        Board[7][0] = new ChessPiece("Rook", 'R', 'b');
        Board[7][7] = new ChessPiece("Rook", 'R', 'b');
        Board[7][1] = new ChessPiece("Knight", 'N', 'b');
        Board[7][6] = new ChessPiece("Knight", 'N', 'b');
        Board[7][5] = new ChessPiece("Bishop", 'B', 'b');
        Board[7][2] = new ChessPiece("Bishop", 'B', 'b');
        // Pawns
        for (int j = 0; j < 8; j++)
            Board[6][j] = new ChessPiece("Pawn", 'P', 'b');
        for (int j = 0; j < 8; j++)
            Board[1][j] = new ChessPiece("Pawn", 'P', 'w');
    }

    void PrintMap()
    {
        cout << "   ";
        for (int i = 0; i < 8; i++)
            cout << i + 1 << " .";
        cout << "\n";

        for (int i = 0; i < 8; i++)
        {
            cout << (char)('A' + i) << " .";
            for (int j = 0; j < 8; j++)
            {
                if (Board[i][j] == NULL)
                    cout << "-- ";
                else
                    cout << Board[i][j]->Color << Board[i][j]->Type << " ";
            }
            cout << "\n";
        }
    }

    int Step(int fx, int fy, int tx, int ty) // f-from,t-to
    {
        /*not authorized movements*/
        try
        {
            /*basic not authorization*/
            if (fx < 0 || fx > 7 || fy < 0 || fy > 7)
                throw("Incorrect Choose\n");
            if (tx < 0 || tx > 7 || ty < 0 || ty > 7)
                throw("Incorrect Movement\n");
            if (Board[fy][fx] == NULL)
                throw("This is Empty Space\n");
            if (turn == 0 && Board[fy][fx]->Color == 'w' || turn == 1 && Board[fy][fx]->Color == 'b')
                throw("Incorrect Choose\n");
            if (Board[ty][tx] != NULL && Board[fy][fx]->Color == Board[ty][tx]->Color)
                throw("Your Piece is blocking the way\n");

            /*For Each Peaces*/
            if (Board[fy][fx]->name == "Pawn")
            {
                if (Board[ty][tx] == NULL && (tx == fx + 1 || tx == fx - 1))
                    throw("Incorrect Movement\n");
                // Pawn can move 2 blocks at first time
                if (abs(tx - fx) > 1 || abs(ty - fy) > 1)
                {
                    if ((fy == 6 && Board[fy][fx]->Color == 'b') || (fy == 1 && Board[fy][fx]->Color == 'w'))
                    {
                        if (abs(ty - fy) > 2)
                            throw("Incorrect Movement\n");
                        if (Board[fy + 1][fx] != NULL&&Board[fy][fx]->Color == 'w'||Board[fy - 1][fx] != NULL&&Board[fy][fx]->Color == 'b')
                            throw ("Your Piece is blocking the way\n");
                    }
                    else
                        throw("Incorrect Movement\n");
                }
                if (fy == ty && tx != fx)
                    throw("Incorrect Movement\n");
                if ((Board[fy][fx]->Color == 'w' && ty < fy) || (Board[fy][fx]->Color == 'b' && ty > fy))
                    throw("Incorrect Movement\n");
            }

            if (Board[fy][fx]->name == "King")
            {
                if (abs(fx - tx) > 1 || abs(fy - ty) > 1)
                    throw("Incorrect Movement\n");
            }

            if (Board[fy][fx]->name == "Queen")
            {
                if (abs(fx - tx) != abs(fy - ty) && fx != tx && fy != ty)
                    throw("Incorrect Movement\n");
                if (fx == tx)
                {
                    for (int i = 1; i < abs(fy - ty) + 1; i++)
                    {
                        if (fy > ty)
                        {
                            if (Board[fy - i][fx] != NULL)
                                throw("Your Piece is blocking the way\n");
                        }
                        else
                        {
                            if (Board[fy + i][fx] != NULL)
                                throw("Your Piece is blocking the way\n");
                        }
                    }
                }
                if (fy == ty)
                {
                    for (int i = 1; i < abs(fx - tx) + 1; i++)
                    {
                        if (fx > tx)
                        {
                            if (Board[fy][fx - i] != NULL)
                                throw("Your Piece is blocking the way\n");
                        }
                        else
                        {
                            if (Board[fy][fx + i] != NULL)
                                throw("Your Piece is blocking the way\n");
                        }
                    }
                }
            }

            if (Board[fy][fx]->name == "Bishop")
            {
                if (abs(fx - tx) != abs(fy - ty))
                    throw("Incorrect Movement\n");
                else
                    for (int i = 1; i < abs(fx - tx); i++)
                    {
                        if (fx > tx && fy > ty)
                        {
                            if (Board[fy - i][fx - i] != NULL)
                                throw("Your Piece is blocking the way\n");
                        }
                        else if (fx > tx && fy < ty)
                        {
                            if (Board[fy + i][fx - i] != NULL)
                                throw("Your Piece is blocking the way\n");
                        }
                        else if (fx < tx && fy > ty)
                        {
                            if (Board[fy - i][fx + i] != NULL)
                                throw("Your Piece is blocking the way\n");
                        }
                        else if (fx < tx && fy < ty)
                        {
                            if (Board[fy + i][fx + i] != NULL)
                                throw("Your Piece is blocking the way\n");
                        }
                    }
            }

            if (Board[fy][fx]->name == "Rook")
            {
                if (fx != tx && fy != ty || abs(fx - tx) == abs(fy - ty))
                    throw("Incorrect Movement\n");
                else
                {
                    if (fx == tx)
                    {
                        for (int i = 1; i < abs(fy - ty) + 1; i++)
                        {
                            if (fy > ty)
                            {
                                if (Board[fy - i][fx] != NULL)
                                    throw("Your Piece is blocking the way\n");
                            }
                            else
                            {
                                if (Board[fy + i][fx] != NULL)
                                    throw("Your Piece is blocking the way\n");
                            }
                        }
                    }
                    if (fy == ty)
                    {
                        for (int i = 1; i < abs(fx - tx) + 1; i++)
                        {
                            if (fx > tx)
                            {
                                if (Board[fy][fx - i] != NULL)
                                    throw("Your Piece is blocking the way\n");
                            }
                            else
                            {
                                if (Board[fy][fx + i] != NULL)
                                    throw("Your Piece is blocking the way\n");
                            }
                        }
                    }
                }
            }

            if (Board[fy][fx]->name == "Knight")
            {
                if (abs(fx - tx) == abs(fy - ty) || fx == tx || fy == ty || abs(fx - tx) > 2 || abs(fy - ty) > 2)
                    throw("Incorrect Movement\n");
            }
        }

        catch (const char *i)
        {
            cout << i;
            return 10;
        }

        /*authorized locations*/
        if (Board[ty][tx] != NULL)
            if (Board[ty][tx]->name == "King" && Board[ty][tx]->Color != Board[fy][fx]->Color) // If the King is dead
            {
                if (Board[fy][fx]->Color == 'w')
                    cout << "White is winner";
                else
                    cout << "Black is winner";
                exit(0);
            }
        if (Board[fy][fx]->name == "Pawn") // Pawn promote
        {
            char c;
            if (Board[fy][fx]->Color == 'w')
                if (ty == 7)
                {
                    while (1)
                    {
                        cout << "Input the Piece initial(in Capital letters) that you want to change:\n";
                        cin >> c;
                        if (Promotion(fx, fy, c, 'w') != 10)
                            break;
                        else
                            cout << "Wrong input\n";
                    }
                }
            if (Board[fy][fx]->Color == 'b')
                if (ty == 0)
                {
                    while (1)
                    {
                        cout << "Input the Piece initial(in Capital letters) that you want to change:\n";
                        cin >> c;
                        if (Promotion(fx, fy, c, 'b') != 10)
                            break;
                        else
                            cout << "Wrong input\n";
                    }
                }
        }

        // Move to authorized location
        Board[ty][tx] = Board[fy][fx];
        Board[fy][fx] = NULL;
        PrintMap();
        return 0;
    }
    int Promotion(int x, int y, char c, char col)
    {
        delete (Board[y][x]);
        if (col == 'w')
        {
            if (c == 'K')
                Board[y][x] = new ChessPiece("King", 'K', 'w');
            else if (c == 'Q')
                Board[y][x] = new ChessPiece("Queen", 'Q', 'w');
            else if (c == 'R')
                Board[y][x] = new ChessPiece("Rook", 'R', 'w');
            else if (c == 'N')
                Board[y][x] = new ChessPiece("Knight", 'N', 'w');
            else if (c == 'B')
                Board[y][x] = new ChessPiece("Bishop", 'B', 'w');
            else
                return 10;
        }
        else
        {
            if (c == 'K')
                Board[y][x] = new ChessPiece("King", 'K', 'b');
            else if (c == 'Q')
                Board[y][x] = new ChessPiece("Queen", 'Q', 'b');
            else if (c == 'R')
                Board[y][x] = new ChessPiece("Rook", 'R', 'b');
            else if (c == 'N')
                Board[y][x] = new ChessPiece("Knight", 'N', 'b');
            else if (c == 'B')
                Board[y][x] = new ChessPiece("Bishop", 'B', 'b');
            else
                return 10;
        }
    }
};

int main()
{
    ChessBoard Board2;
    int i;
    char fx, fy, tx, ty;
    while (1)
    {
        cout << "turn is ";
        if (turn == 0)
            cout << "Black\n";
        else
            cout << "White\n";
        cin >> fx >> fy >> tx >> ty;
        i = Board2.Step(fx - (int)'1', fy - (int)'A', tx - (int)'1', ty - (int)'A');
        if (i != 10)
            turn = !turn;
    }
}