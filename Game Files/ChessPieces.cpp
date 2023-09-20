#include <iostream>
#define cout std::cout
#define cin std::cin
#define string std::string
class ChessPieces
{
protected:
   bool pawn(string, string, int **, int);
   bool pawn(string, string, int, int **);
   bool rook(string, string, int **, int);
   bool bishop(string, string, int **, int);
   bool knight(string, string, int **, int);
   bool king(string, string, int **, int);
   bool queen(string, string, int **, int);
};

bool ChessPieces::pawn(string from, string to, int **board, int turn) // Double Step
{
   int piece = board[to[0] - 'A'][to[1] - '1'];
   switch (turn)
   {
   case 1:
      if (((to[0] != from[0] - 1) || (to[1] != from[1])) && ((2 != from[0] - to[0]) || (to[1] != from[1])) && ((to[0] != from[0] - 1) || (abs(to[1] - from[1]) != 1)))
         return false;
      if ((to[0] == from[0] - 1) && (abs(to[1] - from[1]) == 1) && (piece >= 0))
         return false;
      if ((to[0] == from[0] - 2) && (board[to[0] - 'A'][to[1] - '1'] != 0))
         return false;
      break;
   case 2:
      if (((to[0] != from[0] + 1) || (to[1] != from[1])) && ((to[0] - from[0] != 2) || (to[1] != from[1])) && ((to[0] != from[0] + 1) || (abs(to[1] - from[1]) != 1)))
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
bool ChessPieces::pawn(string from, string to, int turn, int **board) // Single Step
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
bool ChessPieces::rook(string from, string to, int **board, int turn)
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

bool ChessPieces::bishop(string from, string to, int **board, int turn)
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

bool ChessPieces::knight(string from, string to, int **board, int turn)
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

bool ChessPieces::king(string from, string to, int **board, int turn)
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

bool ChessPieces::queen(string from, string to, int **board, int turn)
{
   return (rook(from, to, board, turn) || bishop(from, to, board, turn));
}
