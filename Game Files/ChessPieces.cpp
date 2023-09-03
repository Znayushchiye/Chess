#include <iostream>
#include <map>
#include <vector>
#define boardType vector<vector<string>>
using namespace std;
class ChessPieces
{
protected:
   bool pawn(string, string, boardType, int);
   bool rook(string, string, boardType, int);
   bool bishop(string, string, boardType, int);
   bool knight(string, string, boardType, int);
   bool king(string, string, boardType, int);
   bool queen(string, string, boardType, int);
};

bool ChessPieces::pawn(string from, string to, boardType board, int turn)
{
   string piece = board[(int)to[0]][(int)to[1] - 48];
   switch (turn)
   {
   case 1:
      if (((to[0] != from[0] - 1) || (to[1] != from[1])) && ((to[0] != from[0] - 2) || (to[1] != from[1])) && ((to[0] != from[0] - 1) || (abs(to[1] - from[1]) != 1)))
         return false;
      if ((to[0] == from[0] - 1) && (abs(to[1] - from[1]) == 1) && (piece[0] != 'B') && (piece != "KB") && (piece != "QB"))
         return false;
      if ((from[1] == to[1]) && (piece != "  "))
         return false;
      if ((to[0] == from[0] - 2) && (board[to[0] + 1][to[1] - 48] != "  "))
         return false;
      break;
   case 2:
      if (((to[0] != from[0] + 1) || (to[1] != from[1])) && ((to[0] != from[0] + 2) || (to[1] != from[1])) && ((to[0] != from[0] + 1) || (abs(to[1] - from[1]) != 1)))
         return false;
      if ((to[0] == from[0] + 1) && (abs(to[1] - from[1]) == 1) && (piece[0] != 'W') && (piece[1] != 'W'))
         return false;
      if ((from[1] == to[1]) && (piece != "  "))
         return false;
      if ((to[0] == from[0] + 2) && (board[to[0] - 1][to[1] - 48] != "  "))
         return false;
      break;
   }
   return true;
}

bool ChessPieces::rook(string from, string to, boardType board, int turn)
{
   if (from[0] != to[0] && from[1] != to[1])
      return false;
   if (from[0] == to[0])
   {
      if (from[1] > to[1])
      {
         for (int i = from[1]; i > to[1]; i--)
            if (board[to[0]][i - 48] != "  ")
               return false;
      }
      else
      {
         for (int i = from[1]; i < to[1]; i++)
            if (board[to[0]][i - 48] != "  ")
               return false;
      }
   }
   else
   {
      if (from[0] > to[0])
      {
         for (int i = from[0]; i > to[0]; i--)
         {
            cout << "\"" << board[i][to[1] - 48] << "\"\n";
            if (board[i][to[1] - 48] != "  ")
               return false;
         }
      }
      else
      {
         for (int i = from[0]; i < to[0]; i++)
         {
            cout << "\"" << board[i][to[1] - 48] << "\"\n";
            if (board[i][to[1] - 48] != "  ")
               return false;
         }
      }
   }
   string piece = board[to[0]][to[1] - 48];
   switch (turn)
   {
   case 1:
      if (piece[0] == 'W' || piece[1] == 'W')
         return false;
      return true;
   case 2:
      if (piece[0] != 'W' && piece[1] != 'W' && piece != "  ")
         return false;
      return true;
   }
}

bool ChessPieces::bishop(string from, string to, boardType board, int turn)
{
   if (abs(from[0] - to[0]) != abs(from[1] - to[1]))
      return false;
   if (from[0] > to[0])
   {
      if (from[1] > to[1])
         for (int i = 1; from[0] - i > to[0]; i++)
         {
            if (board[from[0] - i][from[i] - i - 48] != "  ")
               return false;
         }
      else
      {
         for (int i = 1; from[0] - i > to[0]; i++)
         {
            if (board[from[0] - i][from[1] + i - 48] != "  ")
               return false;
         }
      }
   }
   else
   {
      if (from[1] > to[1])
         for (int i = 1; from[0] + i > to[0]; i++)
         {
            if (board[from[0] + i][from[i] - i - 48] != "  ")
               return false;
         }
      else
      {
         for (int i = 1; from[0] + i > to[0]; i++)
         {
            if (board[from[0] + i][from[1] + i - 48] != "  ")
               return false;
         }
      }
   }
   string piece = board[to[0]][to[1] - 48];
   switch (turn)
   {
   case 1:
      if (piece[0] == 'W' || piece[1] != 'W')
         return false;
      break;
   case 2:
      if (piece[0] != 'W' && piece[1] != 'W' && piece != "  ")
         return false;
      break;
   }
   return true;
}

bool ChessPieces::knight(string from, string to, boardType board, int turn)
{
   if ((abs(from[0] - to[0]) != 2 || abs(from[1] - to[1]) != 1) && (abs(from[1] - to[1]) != 2 || abs(from[0] - to[0]) != 1))
      return false;
   string piece = board[to[0]][to[1] - 48];
   switch (turn)
   {
   case 1:
      if (piece[0] == 'W' || piece[1] != 'W')
         return false;
      break;
   case 2:
      if (piece[0] != 'W' && piece[1] != 'W' && piece != "  ")
         return false;
      break;
   }
   return true;
}

bool ChessPieces::king(string from, string to, boardType board, int turn)
{
   if ((abs(from[0] - to[0]) > 1) || (abs(from[1] - to[1]) > 1))
      return false;
   string piece = board[to[0]][to[1] - 48];
   switch (turn)
   {
   case 1:
      if (piece[0] == 'W' || piece[1] != 'W')
         return false;
   case 2:
      if (piece[0] != 'W' && piece[1] != 'W' && piece != "  ")
         return false;
      break;
   }
   return true;
}

bool ChessPieces::queen(string from, string to, boardType board, int turn)
{
   return rook(from, to, board, turn) && bishop(from, to, board, turn);
}
