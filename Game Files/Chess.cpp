#include "ChessPieces.cpp"
#include "Valid.cpp"
#include "Player1.cpp"
#include "Player2.cpp"
class Chess
{
    boardType board;
    map<string, int> pieces;
    map<string, int> countPieces();

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
        vector<string> temp;
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
    cout << endl;
    cout << "      1    2    3    4    5    6    7    8" << endl;
    cout << "    -----------------------------------------" << endl;
    for (int i = 65; i < 73; i++)
    {
        cout << " " << (char)i << " ";
        for (int j = 1; j < 9; j++)
            cout << " | " << board[i][j];
        cout << " | \n    -----------------------------------------\n";
    }
}
bool Chess::gameOver(Player1 p1, Player2 p2)
{
    return p1.hasWon() || p2.hasWon();
}
map<string, int> Chess::countPieces()
{
    map<string, int> piece;
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
    cout << "-----------------------------------------------------";
    cout << "\nWelcome to Chess!!\n";
    cout << "Player 1's name: ";
    string playerName1;
    cin >> playerName1;
    cout << "Player 2's name: ";
    string playerName2;
    cin >> playerName2;
    cout << endl
         << playerName1 << " takes WHITE and " << playerName2 << " takes BLACK.\n\n";
    game.display();
    Player1 pl1(game.getBoard());
    Player2 pl2(game.getBoard());
    int moves = 0;
    do
    {
        if (moves != 0)
            game.display();
        cout << "\nFor " << playerName1 << ",\n";
        game.setBoard(pl1.turn(game.getBoard()));
        moves++;
        if (pl1.hasWon() || moves == 75)
            break;
        game.display();
        cout << "\nFor " << playerName2 << ",\n";
        game.setBoard(pl2.turn(game.getBoard()));
        moves++;

    } while (!game.gameOver(pl1, pl2));
    if (moves > 75)
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