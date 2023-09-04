#include <unistd.h>
#include "ChessPieces.cpp"
#include "Valid.cpp"
#include "Player1.cpp"
#include "Player2.cpp"
class Chess
{
    boardType board;
    std::map<std::string, int> pieces;
    std::map<std::string, int> countPieces();

public:
    Chess();
    void display();
    bool gameOver(Player1, Player2);
    void setBoard(boardType);
    boardType getBoard();
};
Chess::Chess()
{
    for (int i = 0; i < 73; i++)
    {
        std::vector<std::string> temp;
        for (int j = 0; j < 9; j++)
            temp.push_back("  ");
        board.push_back(temp);
    }

    board[65][1] = board[65][8] = "BR";
    board[65][2] = board[65][7] = "BK";
    board[65][3] = board[65][6] = "BB";
    for (int i = 1; i < 9; i++)
        board[66][i] = "BP";
    board[65][4] = "KB";
    board[65][5] = "QB";

    board[72][1] = board[72][8] = "WR";
    board[72][2] = board[72][7] = "WK";
    board[72][3] = board[72][6] = "WB";
    for (int i = 1; i < 9; i++)
        board[71][i] = "WP";
    board[72][4] = "QW";
    board[72][5] = "KW";

    pieces = countPieces();
}
void Chess::display()
{
    std::cout << std::endl;
    std::cout << "      1    2    3    4    5    6    7    8" << std::endl;
    std::cout << "    -----------------------------------------" << std::endl;
    for (int i = 65; i < 73; i++)
    {
        std::cout << " " << (char)i << " ";
        for (int j = 1; j < 9; j++)
            std::cout << " | " << board[i][j];
        std::cout << " | \n    -----------------------------------------\n";
    }
}
bool Chess::gameOver(Player1 p1, Player2 p2)
{
    return p1.hasWon() || p2.hasWon();
}
std::map<std::string, int> Chess::countPieces()
{
    std::map<std::string, int> piece;
    for (auto itr : board)
    {
        for (int i = 1; i < 9; i++)
            piece[itr[i]]++;
    }
    return piece;
}
void Chess::setBoard(boardType b)
{
    board = b;
}
boardType Chess::getBoard()
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