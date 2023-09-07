#include <unistd.h>
#include <map>
#include <iostream>
#include "Driver.cpp"
#include "Player1.cpp"
#include "Player2.cpp"

class Chess
{
    int **board;
    std::map<int, int> pieces;
    std::map<int, int> countPieces();

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
        {
            board[i][j] = 0;
        }
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
void Chess::display()
{
    std::cout << std::endl;
    std::cout << "      1    2    3    4    5    6    7    8" << std::endl;
    std::cout << "    -----------------------------------------" << std::endl;
    for (int i = 0; i < 8; i++)
    {
        std::cout << " " << (char)(i + 65) << " ";
        for (int j = 0; j < 8; j++)
        {
            int piece = board[i][j];
            std::cout << " | ";
            switch (abs(piece))
            {
            case 0:
                std::cout << "  ";
                break;
            case 1:
                std::cout << ((piece < 0) ? "B" : "W") << "P";
                break;
            case 2:
                std::cout << ((piece < 0) ? "B" : "W") << "R";
                break;
            case 3:
                std::cout << ((piece < 0) ? "B" : "W") << "K";
                break;
            case 4:
                std::cout << ((piece < 0) ? "B" : "W") << "B";
                break;
            case 5:
                std::cout << "Q" << ((piece < 0) ? "B" : "W");
                break;
            case 6:
                std::cout << "K" << ((piece < 0) ? "B" : "W");
                break;
            }
        }
        std::cout << " | \n    -----------------------------------------\n";
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
    std::cout << "-----------------------------------------------------";
    std::cout << "\nWelcome to Chess!!\n";
    std::cout << "Player 1's name: ";
    std::string playerName1;
    std::cin >> playerName1;
    std::cout << "Player 2's name: ";
    std::string playerName2;
    std::cin >> playerName2;
    usleep(500000);
    std::cout << std::endl
              << playerName1 << " takes WHITE and " << playerName2 << " takes BLACK.\n";
    usleep(500000);
    game.display();

    Player1 pl1(game.getBoard());
    Player2 pl2(game.getBoard());
    int moves = 0;
    std::cout << "\nEnter valid cell positions (e.g, A2, B7).\n ";
    do
    {
        if (moves != 0)
            game.display();
        std::cout << "\n"
                  << playerName1 << "'s Turn,\n";
        game.setBoard(pl1.turn(game.getBoard()));
        moves++;
        if (game.gameOver(pl1, pl2) || moves == 75)
            break;
        game.display();
        std::cout << "\nFor " << playerName2 << ",\n";
        game.setBoard(pl2.turn(game.getBoard()));
        moves++;
    } while (!game.gameOver(pl1, pl2));
    if (moves == 75)
        std::cout << "Match Draw! GG, everyone..!";
    else if (pl1.hasWon())
        std::cout << playerName1 << " has won! Congratulations..!!";
    else
        std::cout << playerName2 << " has won! Congratulations..!!";
    std::cout << "\n\nFinal Board:\n";
    game.display();
    std::cout << "-----------------------------------------------------";
    return 0;
}