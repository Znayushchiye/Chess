#include <iostream>
#include <map>
#include <vector>
#define boardType std::vector<std::vector<std::string>>
class ChessPieces
{
protected:
   bool pawn(std::string, std::string, boardType, int);
   bool rook(std::string, std::string, boardType, int);
   bool bishop(std::string, std::string, boardType, int);
   bool knight(std::string, std::string, boardType, int);
   bool king(std::string, std::string, boardType, int);
   bool queen(std::string, std::string, boardType, int);
};

bool ChessPieces::pawn(std::string from, std::string to, boardType board, int turn)
{
   std::string piece = board[(int)to[0]][(int)to[1] - 48];
   switch (turn)
   {
   case 1:
      if (((to[0] != from[0] - 1) || (to[1] != from[1])) && ((to[0] != from[0] - 2) || (to[1] != from[1])) && ((to[0] != from[0] - 1) || (abs(to[1] - from[1]) != 1)))
         return false;
      if ((to[0] == from[0] - 1) && (abs(to[1] - from[1]) == 1) && (piece[0] != 'B') && (piece != "KB") && (piece != "QB"))
         return false;
      if ((to[0] == from[0] - 2) && (board[to[0] + 1][to[1] - 48] != "  "))
         return false;
      break;
   case 2:
      if (((to[0] != from[0] + 1) || (to[1] != from[1])) && ((to[0] != from[0] + 2) || (to[1] != from[1])) && ((to[0] != from[0] + 1) || (abs(to[1] - from[1]) != 1)))
         return false;
      if ((to[0] == from[0] + 1) && (abs(to[1] - from[1]) == 1) && (piece[0] != 'W') && (piece[1] != 'W'))
         return false;
      if ((to[0] == from[0] + 2) && (board[to[0] - 1][to[1] - 48] != "  "))
         return false;
      break;
   }
   if ((from[1] == to[1]) && (piece != "  "))
      return false;
   return true;
}

bool ChessPieces::rook(std::string from, std::string to, boardType board, int turn)
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
            std::cout << "\"" << board[i][to[1] - 48] << "\"\n";
            if (board[i][to[1] - 48] != "  ")
               return false;
         }
      }
      else
      {
         for (int i = from[0]; i < to[0]; i++)
         {
            std::cout << "\"" << board[i][to[1] - 48] << "\"\n";
            if (board[i][to[1] - 48] != "  ")
               return false;
         }
      }
   }
   std::string piece = board[to[0]][to[1] - 48];
   switch (turn)
   {
   case 1:
      if (piece[0] == 'W' || piece[1] == 'W')
         return false;
      break;
   case 2:
      if (piece[0] != 'W' && piece[1] != 'W' && piece != "  ")
         return false;
      break;
   }
   return true;
}

bool ChessPieces::bishop(std::string from, std::string to, boardType board, int turn)
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
   std::string piece = board[to[0]][to[1] - 48];
   switch (turn)
   {
   case 1:
      if (piece[0] == 'W' || piece[1] == 'W')
         return false;
      break;
   case 2:
      if (piece[0] != 'W' && piece[1] != 'W' && piece != "  ")
         return false;
      break;
   }
   return true;
}

bool ChessPieces::knight(std::string from, std::string to, boardType board, int turn)
{
   if ((abs(from[0] - to[0]) != 2 || abs(from[1] - to[1]) != 1) && (abs(from[1] - to[1]) != 2 || abs(from[0] - to[0]) != 1))
      return false;
   std::string piece = board[to[0]][to[1] - 48];
   switch (turn)
   {
   case 1:
      if (piece[0] == 'W' || piece[1] == 'W')
         return false;
      break;
   case 2:
      if (piece[0] != 'W' && piece[1] != 'W' && piece != "  ")
         return false;
      break;
   }
   return true;
}

bool ChessPieces::king(std::string from, std::string to, boardType board, int turn)
{
   if ((abs(from[0] - to[0]) > 1) || (abs(from[1] - to[1]) > 1))
      return false;
   std::string piece = board[to[0]][to[1] - 48];
   switch (turn)
   {
   case 1:
      if (piece[0] == 'W' || piece[1] == 'W')
         return false;
      break;
   case 2:
      if (piece[0] != 'W' && piece[1] != 'W' && piece != "  ")
         return false;
      break;
   }
   return true;
}

bool ChessPieces::queen(std::string from, std::string to, boardType board, int turn)
{
   return (rook(from, to, board, turn) || bishop(from, to, board, turn));
}
