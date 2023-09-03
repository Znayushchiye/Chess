#include <iostream>
#include <map>
#include <vector>
using namespace std;
class Player1
{
   map<char, vector<string>> board;
   string validPos(string);
   bool pawn(string, string);
   bool rook(string, string);
   bool bishop(string, string);
   bool knight(string, string);
   bool king(string, string);
   bool queen(string, string);
   bool isValid(string);
   bool isValid(string, string);
   bool canMove(string, string);
   map<string, int> countPiece();
   map<char, vector<string>> move(string, string);

public:
   Player1(map<char, vector<string>>);
   map<char, vector<string>> turn();
   bool hasWon();
};
Player1::Player1(map<char, vector<string>> board)
{
   this->board = board;
}
string Player1::validPos(string str) // Finished
{
   string temp = str;
   str = "";
   for (char ch : temp)
      str += toupper(ch);
   int i = 0;
   char ch;
   temp = "";
   ch = str[i++];
   while (ch != '\0')
   {
      if (!isalnum(ch))
         continue;
      if ((ch < 'A' || ch > 'H') && (ch < '1' || ch > '8'))
         return "-1";
      temp += ch;
      ch = str[i++];
   }
   if (temp.length() != 2)
      return "-1";
   str = temp;
   if (!isalpha(str[0]))
      swap(str[0], str[1]);
   return str;
}
bool Player1::isValid(string from) // Finished
{
   string temp = validPos(from);
   if (temp == "-1")
      return false;
   string piece = board[temp[0]][temp[1]];
   if (piece == "  " || piece[0] == 'B' || piece == "KB" || piece == "QB")
      return false;
   return true;
}
bool Player1::isValid(string to, string from) // Finished
{
   string temp = validPos(to);
   if (temp == "-1")
      return false;
   to = temp;
   if (from == to)
      return false;
   cout << "CanMove called";
   return canMove(to, from);
}
bool Player1::pawn(string from, string to) // Finished
{
   cout << "1st Check";
   if (((to[0] != from[0] - 1) || (to[1] != from[1])) && ((to[0] != from[0] - 2) || (to[1] != from[1])) && ((to[0] != from[0] - 1) || (abs(to[1] - from[1]) != 1)))
      return false;
   string piece = board[to[0]][to[1]];
   cout << piece << endl;
   cout << "2nd Check\n";
   if ((to[0] == from[0] - 1) && (abs(to[1] - from[1]) == 1) && (piece[0] != 'B') && (piece != "KB") && (piece != "QB"))
      return false;
   cout << "3rd Check\n";
   if ((from[1] == to[1]) && (piece != "  "))
      return false;
   cout << "4th Check\n";
   if ((to[0] == from[0] - 2) && (board[to[0] - 1][to[1]] != "  "))
      return false;
   cout << "Can move pawn";
   return true;
}
bool Player1::rook(string from, string to) // Finished
{
   if (from[0] != to[0] && from[1] != to[1])
      return false;
   if (from[0] == to[0])
      for (int i = from[1]; i < to[1]; i++)
      {
         string pos = board[to[0]][i];
         if (pos != "  ")
            return false;
      }
   else
      for (char i = from[0]; i < to[0]; i++)
      {
         string pos = board[(char)i][to[1]];
         if (pos != "  ")
            return false;
      }
   string piece = board[to[0]][to[1]];
   if (piece[0] != 'B' && piece != "KB" && piece != "QB" && piece != "  ")
      return false;
   return true;
}
bool Player1::bishop(string from, string to) // Finished
{
   if ((from[0] - to[0]) != (from[1] - to[1]))
      return false;
   if (from[0] > to[0])
   {
      if (from[1] > to[1])
         for (int i = 1; from[0] - i > to[0]; i++)
         {
            if (board[from[0] - i][from[i] - i] != "  ")
               return false;
         }
      else
      {
         for (int i = 1; from[0] - i > to[0]; i++)
         {
            if (board[from[0] - i][from[1] + i] != "  ")
               return false;
         }
      }
   }
   else
   {
      if (from[1] > to[1])
         for (int i = 1; from[0] + i > to[0]; i++)
         {
            if (board[from[0] + i][from[i] - i] != "  ")
               return false;
         }
      else
      {
         for (int i = 1; from[0] + i > to[0]; i++)
         {
            if (board[from[0] + i][from[1] + i] != "  ")
               return false;
         }
      }
   }
   string piece = board[to[0]][to[1]];
   if (piece[0] != 'B' && piece != "KB" && piece != "QB" && piece != "  ")
      return false;
   return true;
}
bool Player1::knight(string from, string to) // Finished
{
   if ((abs(from[0] - to[0]) > 1 && abs(from[1] - to[1]) != 2) || (abs(from[1] - to[1]) > 1 && abs(from[0] - to[0]) != 2))
      return false;
   string piece = board[to[0]][to[1]];
   if (piece[0] != 'B' && piece != "KB" && piece != "QB" && piece != "  ")
      return false;
   return true;
}
bool Player1::king(string from, string to) // Finished
{
   if ((abs(from[0] - to[0]) > 1) || (abs(from[1] - to[1]) > 1))
      return false;
   string piece = board[to[0]][to[1]];
   if (piece[0] != 'B' && piece != "KB" && piece != "QB" && piece != "  ")
      return false;
   return true;
}
bool Player1::queen(string from, string to) // Finished
{
   return rook(from, to) && bishop(from, to);
}
bool Player1::canMove(string to, string from)
{
   string piece = board[from[0]][(int)from[1]];
   cout << piece << endl;
   if (piece[0] == 'B')
      switch (piece[1])
      {
      case 'P':
         return pawn(from, to);
      case 'R':
         return rook(from, to);
      case 'B':
         return bishop(from, to);
      case 'K':
         return knight(from, to);
      }
   else if (piece == "KB")
      return king(from, to);
   return queen(from, to);
}
map<char, vector<string>> Player1::move(string from, string to)
{
   board[to[0]][to[1]] = board[from[0]][from[1]];
   board[from[0]][from[1]] = "  ";
   return board;
}
map<string, int> Player1::countPiece()
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
bool Player1::hasWon()
{
   map<string, int> pieces = countPiece();
   if (pieces["BK"] == 0)
      return true;
   return false;
}
map<char, vector<string>> Player1::turn()
{
   cout << "Enter the cell position of the piece to move: ";
   string from;
   cin >> from;
   while (!isValid(from))
   {
      cout << "\nInvalid input! Enter a valid cell position (e.g., A2).";
      cin >> from;
   }
   cout << "Enter the cell position where you want to move the piece: ";
   string to;
   cin >> to;
   while (!isValid(to, from))
   {
      cout << "\nInvalid input! Enter a valid cell position or check if the piece can move to the specified location.\nCheck if the path isn't blocked." << endl;
      cin >> to;
   }
   return move(from, to);
}