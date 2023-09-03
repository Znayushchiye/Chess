#include <iostream>
#include <map>
#include <vector>
using namespace std;
class Player2
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
   Player2(map<char, vector<string>>);
   map<char, vector<string>> turn();
   bool hasWon();
};
Player2::Player2(map<char, vector<string>> board)
{
   this->board = board;
}
string Player2::validPos(string str) // Finished
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
bool Player2::isValid(string from) // Finished
{
   string temp = validPos(from);
   if (temp == "-1")
      return false;
   from = temp;
   string piece = board[from[0]][from[1]];
   if (piece == "  " || piece[0] == 'W' || piece == "KW" || piece == "QW")
      return false;
   return true;
}
bool Player2::isValid(string to, string from) // Finished
{
   string temp = validPos(to);
   if (temp == "-1")
      return false;
   to = temp;
   if (from == to)
      return false;
   return canMove(to, from);
}
bool Player2::pawn(string from, string to)
{
   if (((to[0] != from[0] - 1) || (to[1] != from[1])) && ((to[0] != from[0] - 2) || (to[1] != from[1])) && ((to[0] != from[0] - 1) || (abs(to[1] - from[1]) != 1)))
      return false;
   string piece = board[to[0]][to[1]];
   if ((to[0] == from[0] - 1) && (abs(to[1] - from[1]) == 1) && (piece[0] != 'B') && (piece != "KB") && (piece != "QB"))
      return false;
   if ((from[1] == to[1]) && (piece != "  "))
      return false;
   if ((to[0] == from[0] - 2) && (board[to[0] + 1][to[1]] != "  "))
      return false;
   return true;
}
bool Player2::rook(string from, string to)
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
   if (piece[0] != 'W' && piece != "KW" && piece != "QW" && piece != "  ")
      return false;
   return true;
}
bool Player2::bishop(string from, string to)
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
   if (piece[0] != 'W' && piece != "KW" && piece != "QW" && piece != "  ")
      return false;
   return true;
}
bool Player2::knight(string from, string to)
{
   if ((abs(from[0] - to[0]) > 1 && abs(from[1] - to[1]) != 2) || (abs(from[1] - to[1]) > 1 && abs(from[0] - to[0]) != 2))
      return false;
   string piece = board[to[0]][to[1]];
   if (piece[0] != 'W' && piece != "KW" && piece != "QW" && piece != "  ")
      return false;
   return true;
}
bool Player2::king(string from, string to)
{
   if ((abs(from[0] - to[0]) > 1) || (abs(from[1] - to[1]) > 1))
      return false;
   string piece = board[to[0]][to[1]];
   if (piece[0] != 'W' && piece != "KW" && piece != "QW" && piece != "  ")
      return false;
   return true;
}
bool Player2::queen(string from, string to)
{
   return rook(from, to) && bishop(from, to);
}
bool Player2::canMove(string to, string from)
{
   string piece = board[from[0]][from[1]];
   if (piece[0] == 'W')
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
   else if (piece == "KW")
      return king(from, to);
   return queen(from, to);
}
map<char, vector<string>> Player2::move(string from, string to)
{
   board[to[0]][to[1]] = board[from[0]][from[1]];
   board[from[0]][from[1]] = "  ";
   return board;
}
map<string, int> Player2::countPiece()
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
bool Player2::hasWon()
{
   map<string, int> pieces = countPiece();
   if (pieces["WK"] == 0)
      return true;
   return false;
}
map<char, vector<string>> Player2::turn()
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
      cout << "\nInvalid input! Enter a valid cell position or check if the piece can move to the specified location." << endl;
      cin >> to;
   }
   return move(from, to);
}