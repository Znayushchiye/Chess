#include <unistd.h>
#include <map>
#include <iostream>
#include "./Game Files/Driver.cpp"
#include "./Game Files/Player1.cpp"
#include "./Game Files/Player2.cpp"

class Chess
{
    int **board;
    std::map<int, int> pieces;
    std::map<int, int> countPieces();
    void print(int);

public:
    Chess();
    void display();
    bool gameOver(Player1, Player2);
    void setBoard(int **);
    int **getBoard();
};
Chess::Chess()
{
    board = new int *[8];
    for (int i = 0; i < 8; i++)
    {
        board[i] = new int[8];
        for (int j = 0; j < 8; j++)
            board[i][j] = 0;
    }

    for (int i = 0; i < 8; i++)
        board[1][i] = -1;
    board[0][0] = board[0][7] = -2;
    board[0][1] = board[0][6] = -3;
    board[0][2] = board[0][5] = -4;
    board[0][3] = -5;
    board[0][4] = -6;

    for (int i = 0; i < 8; i++)
        board[6][i] = 1;
    board[7][0] = board[7][7] = 2;
    board[7][1] = board[7][6] = 3;
    board[7][2] = board[7][5] = 4;
    board[7][4] = 5;
    board[7][3] = 6;

    pieces = countPieces();
}
void Chess::print(int piece)
{
    if (piece == 0)
    {
        cout << "  ";
    }
    else if (abs(piece) < 5)
    {
        cout << ((piece < 0) ? "B" : "W");
        switch (abs(piece))
        {
        case 1:
            cout << "P";
            break;
        case 2:
            cout << "R";
            break;
        case 3:
            cout << "K";
            break;
        case 4:
            cout << "B";
            break;
        }
    }
    else
    {
        switch (abs(piece))
        {
        case 5:
            cout << "Q";
            break;
        case 6:
            cout << "K";
            break;
        }
        cout << ((piece < 0) ? "B" : "W");
    }
}
void Chess::display()
{
    cout << std::endl;
    cout << "      1    2    3    4    5    6    7    8" << std::endl;
    cout << "    -----------------------------------------" << std::endl;
    for (int i = 0; i < 8; i++)
    {
        cout << " " << (char)(i + 65) << " ";
        for (int j = 0; j < 8; j++)
        {
            int piece = board[i][j];
            cout << " | ";
            print(piece);
        }
        cout << " | \n    -----------------------------------------\n";
    }
}
bool Chess::gameOver(Player1 p1, Player2 p2)
{
    return p1.hasWon() || p2.hasWon();
}
std::map<int, int> Chess::countPieces()
{
    std::map<int, int> piece;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            piece[board[i][j]]++;
    return piece;
}
void Chess::setBoard(int **b)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            board[i][j] = b[i][j];
}
int **Chess::getBoard()
{
    return board;
}
int main()
{
    Chess game;
    cout << "-----------------------------------------------------";
    cout << "\nWelcome to Chess!!\n";
    cout << "Player 1's name: ";
    std::string playerName1;
    cin >> playerName1;
    cout << "Player 2's name: ";
    std::string playerName2;
    cin >> playerName2;
    usleep(500000);
    cout << std::endl
         << playerName1 << " takes WHITE and " << playerName2 << " takes BLACK.\n";
    usleep(500000);
    game.display();

    Player1 pl1(game.getBoard());
    Player2 pl2(game.getBoard());
    int moves = 0;
    cout << "\nEnter valid cell positions (e.g, A2, B7).\n ";
    do
    {
        if (moves != 0)
            game.display();
        cout << "\n"
             << playerName1 << "'s Turn,\n";
        game.setBoard(pl1.turn(game.getBoard()));
        moves++;
        if (game.gameOver(pl1, pl2) || moves == 75)
            break;
        game.display();
        cout << "\nFor " << playerName2 << ",\n";
        game.setBoard(pl2.turn(game.getBoard()));
        moves++;
    } while (!game.gameOver(pl1, pl2));
    if (moves == 75)
        cout << "Match Draw! GG, everyone..!";
    else if (pl1.hasWon())
        cout << playerName1 << " has won! Congratulations..!!";
    else
        cout << playerName2 << " has won! Congratulations..!!";
    cout << "\n\nFinal Board:\n";
    game.display();
    cout << "-----------------------------------------------------";
    return 0;
}