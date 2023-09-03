#include <iostream>
#include <map>
#include <vector>
#include "Player1.cpp"
#include "Player2.cpp"
using namespace std;

class Chess
{

    map<char, vector<string>> board = {
        {'A', {"  ", "BR", "BK", "BB", "KB", "QB", "BB", "BK", "BR"}},
        {'B', {"  ", "BP", "BP", "BP", "BP", "BP", "BP", "BP", "BP"}},
        {'C', {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "}},
        {'D', {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "}},
        {'E', {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "}},
        {'F', {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "}},
        {'G', {"  ", "WP", "WP", "WP", "WP", "WP", "WP", "WP", "WP"}},
        {'H', {"  ", "WR", "WK", "WB", "QW", "KW", "WB", "WK", "WR"}},
    };
    map<string, int> pieces;
    map<string, int> countPieces();

public:
    Chess();
    void display();
    bool gameOver(Player1, Player2);
    void setBoard(map<char, vector<string>>);
    map<char, vector<string>> getBoard();
};
Chess::Chess()
{
    pieces = countPieces();
}
void Chess::display()
{
    cout << endl;
    cout << "      1    2    3    4    5    6    7    8" << endl;
    cout << "    -----------------------------------------" << endl;
    for (auto i : board)
    {
        cout << " " << i.first << " ";
        for (int j = 1; j < 9; j++)
            cout << " | " << (i.second)[j];
        cout << " | " << endl
             << "    -----------------------------------------" << endl;
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
        vector<string> row = itr.second;
        for (string pc : row)
            piece[pc]++;
    }
    return piece;
}
void Chess::setBoard(map<char, vector<string>> b)
{
    board = b;
}
map<char, vector<string>> Chess::getBoard()
{
    return board;
}
int main()
{
    Chess game;
    cout << "-----------------------------------------------------";
    cout << "\nWelcome to Chess!!\n";
    cout << "Player 1's name: ";
    string human1;
    cin >> human1;
    cout << "Player 2's name: ";
    string human2;
    cin >> human2;
    cout << endl
         << human1 << " takes WHITE and " << human2 << " takes BLACK.\n\n";
    game.display();
    cout << "\nFor " << human1 << ",\n";
    Player1 pl1(game.getBoard());
    Player2 pl2(game.getBoard());
    int moves = 0;
    do
    {
        if (moves != 0)
            game.display();
        game.setBoard(pl1.turn());
        moves++;
        if (pl1.hasWon() || moves > 75)
            break;
        game.display();
        game.setBoard(pl2.turn());
        moves++;

    } while (!game.gameOver(pl1, pl2));
    if (moves > 75)
        cout << "Match Draw! GG, everyone..!";
    else if (pl1.hasWon())
        cout << human1 << " has won! Congratulations..!!";
    else
        cout << human2 << " has won! Congratulations..!!";
    cout << "\n\nFinal Board:\n";
    game.display();
    cout << "-----------------------------------------------------";
    return 0;
}