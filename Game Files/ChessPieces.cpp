#include <iostream>
#include <unordered_map>
#include <vector>
#define map unordered_map
#define cout std::cout
#define cin std::cin
class ChessPieces
{
protected:
   bool pawn(std::string, std::string, int **, int);
   bool pawn(std::string, std::string, int, int **);
   bool rook(std::string, std::string, int **, int);
   bool bishop(std::string, std::string, int **, int);
   bool knight(std::string, std::string, int **, int);
   bool king(std::string, std::string, int **, int);
   bool queen(std::string, std::string, int **, int);
};

bool ChessPieces::pawn(std::string from, std::string to, int **board, int turn)
{
   int piece = board[to[0] - 'A'][to[1] - '1'];
   switch (turn)
   {
   case 1:
      if (((to[0] != from[0] - 1) || (to[1] != from[1])) && ((to[0] != from[0] - 2) || (to[1] != from[1])) && ((to[0] != from[0] - 1) || (abs(to[1] - from[1]) != 1)))
         return false;
      if ((to[0] == from[0] - 1) && (abs(to[1] - from[1]) == 1) && (piece >= 0))
         return false;
      if ((to[0] == from[0] - 2) && (board[to[0] - 'A'][to[1] - '1'] != 0))
         return false;
      break;
   case 2:
      if (((to[0] != from[0] + 1) || (to[1] != from[1])) && ((to[0] != from[0] + 2) || (to[1] != from[1])) && ((to[0] != from[0] + 1) || (abs(to[1] - from[1]) != 1)))
         return false;
      if ((to[0] == from[0] + 1) && (abs(to[1] - from[1]) == 1) && (piece <= 0))
         return false;
      if ((to[0] == from[0] + 2) && (board[to[0] - 'A'][to[1] - '1'] != 0))
         return false;
      break;
   }
   if ((from[1] == to[1]) && (piece != 0))
      return false;
   return true;
}
bool ChessPieces::pawn(std::string from, std::string to, int turn, int **board) // CHECK LOGIC
{
   int piece = board[to[0] - 'A'][to[1] - '1'];
   switch (turn)
   {
   case 1:
      if (((to[0] != from[0] - 1) || (to[1] != from[1])) && ((to[0] != from[0] - 1) || (abs(to[1] - from[1]) != 1)))
         return false;
      if ((to[0] == from[0] - 1) && (abs(to[1] - from[1]) == 1) && (piece >= 0))
         return false;
      if ((to[0] == from[0] - 2) && (board[to[0] - 'A'][to[1] - '1'] != 0))
         return false;
      break;
   case 2:
      if (((to[0] != from[0] + 1) || (to[1] != from[1])) && ((to[0] != from[0] + 1) || (abs(to[1] - from[1]) != 1)))
         return false;
      if ((to[0] == from[0] + 1) && (abs(to[1] - from[1]) == 1) && (piece <= 0))
         return false;
      if ((to[0] == from[0] + 2) && (board[to[0] - 'A'][to[1] - '1'] != 0))
         return false;
      break;
   }
   if ((from[1] == to[1]) && (piece != 0))
      return false;
   return true;
}
bool ChessPieces::rook(std::string from, std::string to, int **board, int turn)
{
   if (from[0] != to[0] && from[1] != to[1])
      return false;
   /* if (from[0] == to[0])
   {
      if (from[1] < to[1])
      {
         for (int i = from[1]; i < to[1]; i++)
            if (board[to[0]][i - 48] != 0)
               return false;
      }
   } */
   if (from[0] < to[0])
   {
      for (int i = from[0] - 'A' + 1; i < (to[0] - 'A'); i++)
      {
         cout << "piece = \'" << board[i][to[1] - '1'] << "\'" << std::endl;
         if (board[i][to[1] - '1'] != 0)
            return false;
      }
   }
   else if (from[0] > to[0])
   {
      for (int i = from[0] - 66; i > to[0] - 65; i--)
      {
         cout << "Printed = \'" << i << ", " << to[1] << "\'" << std::endl;
         cout << "piece = \'" << board[i][to[1] - 48] << "\'" << std::endl;
         if (board[i][to[1] - 48] != 0)
            return false;
      }
   }
   else if (from[1] > to[1])
   {
      for (int i = from[1] - 49; i > to[1] - 48; i--)
      {
         cout << "piece = \'" << board[to[0] - 65][i] << "\'" << std::endl;
         if (board[to[0] - 65][i] != 0)
            return false;
      }
   }
   else
   {
      for (int i = from[1] - 47; i < to[1] - 48; i++)
      {
         cout << "piece = \'" << board[to[0] - 65][i] << "\'" << std::endl;
         if (board[to[0] - 65][i] != 0)
            return false;
      }
   }

   cout << "2nd check passed\n";
   int piece = board[to[0] - 65][to[1] - 48];
   switch (turn)
   {
   case 1:
      if (piece > 0)
         return false;
      break;
   case 2:
      if (piece < 0)
         return false;
      break;
   }
   cout << "Valid move\n";
   return true;
}

bool ChessPieces::bishop(std::string from, std::string to, int **board, int turn)
{
   if (abs(from[0] - to[0]) != abs(from[1] - to[1]))
      return false;
   if (from[0] > to[0])
   {
      if (from[1] > to[1])
         for (int i = 1; (from[0] - i) > to[0]; i++)
         {
            if (board[from[0] - i - 65][from[i] - i - 48] != 0)
               return false;
         }
      else
      {
         for (int i = 1; (from[0] - i) > to[0]; i++)
         {
            if (board[from[0] - i - 65][from[1] + i - 48] != 0)
               return false;
         }
      }
   }
   else
   {
      if (from[1] > to[1])
         for (int i = 1; (from[0] + i) > to[0]; i++)
         {
            if (board[from[0] + i - 65][from[i] - i - 48] != 0)
               return false;
         }
      else
      {
         for (int i = 1; (from[0] + i) > to[0]; i++)
         {
            if (board[from[0] + i - 65][from[1] + i - 48] != 0)
               return false;
         }
      }
   }
   int piece = board[to[0] - 65][to[1] - 48];
   switch (turn)
   {
   case 1:
      if (piece > 0)
         return false;
      break;
   case 2:
      if (piece < 0)
         return false;
      break;
   }
   return true;
}

bool ChessPieces::knight(std::string from, std::string to, int **board, int turn)
{
   if ((abs(from[0] - to[0]) != 2 || abs(from[1] - to[1]) != 1) && (abs(from[1] - to[1]) != 2 || abs(from[0] - to[0]) != 1))
      return false;
   int piece = board[to[0] - 65][to[1] - 48];
   switch (turn)
   {
   case 1:
      if (piece > 1)
         return false;
      break;
   case 2:
      if (piece < 0)
         return false;
      break;
   }
   return true;
}

bool ChessPieces::king(std::string from, std::string to, int **board, int turn)
{
   if ((abs(from[0] - to[0]) > 1) || (abs(from[1] - to[1]) > 1))
      return false;
   int piece = board[to[0] - 65][to[1] - 48];
   switch (turn)
   {
   case 1:
      if (piece > 0)
         return false;
      break;
   case 2:
      if (piece < 0)
         return false;
      break;
   }
   return true;
}

bool ChessPieces::queen(std::string from, std::string to, int **board, int turn)
{
   return (rook(from, to, board, turn) || bishop(from, to, board, turn));
}
