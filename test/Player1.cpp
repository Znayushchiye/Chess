#include "Valid.cpp"
class Player1
{
protected:
   boardType board;
   bool pawn(string, string);
   bool rook(string, string);
   bool bishop(string, string);
   bool knight(string, string);
   bool king(string, string);
   bool queen(string, string);
   bool canMove(string, string);
   map<string, int> countPiece();

public:
   Player1(boardType);
   boardType move(string, string);
   void setBoard(boardType);
   boardType turn(boardType);
   bool hasWon();
};
Player1::Player1(boardType board)
{
   setBoard(board);
}
void Player1::setBoard(boardType board)
{
   this->board = board;
}
bool Player1::pawn(string from, string to) // Finished
{
   cout << "1st Check";
   if (((to[0] != from[0] - 1) || (to[1] != from[1])) && ((to[0] != from[0] - 2) || (to[1] != from[1])) && ((to[0] != from[0] - 1) || (abs(to[1] - from[1]) != 1)))
      return false;
   string piece = board[(int)to[0]][(int)to[1] - 48];
   cout << piece << endl;
   cout << "2nd Check\n";
   if ((to[0] == from[0] - 1) && (abs(to[1] - from[1]) == 1) && (piece[0] != 'B') && (piece != "KB") && (piece != "QB"))
      return false;
   cout << "3rd Check\n";
   if ((from[1] == to[1]) && (piece != "  "))
      return false;
   cout << "4th Check\n";
   if ((to[0] == from[0] - 2) && (board[to[0] + 1][to[1] - 48] != "  "))
      return false;
   cout << "Can move pawn";
   return true;
}
bool Player1::rook(string from, string to) // Finished
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
   if (piece[0] == 'W' || piece[1] != 'W')
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
   string piece = board[(int)to[0]][(int)to[1] - 48];
   if (piece[0] == 'W' || piece[1] != 'W')
      return false;
   return true;
}
bool Player1::knight(string from, string to) // Finished
{
   if ((abs(from[0] - to[0]) > 1 && abs(from[1] - to[1]) != 2) || (abs(from[1] - to[1]) > 1 && abs(from[0] - to[0]) != 2))
      return false;
   string piece = board[(int)to[0]][(int)to[1] - 48];
   if (piece[0] == 'W' || piece[1] != 'W')
      return false;
   return true;
}
bool Player1::king(string from, string to) // Finished
{
   if ((abs(from[0] - to[0]) > 1) || (abs(from[1] - to[1]) > 1))
      return false;
   string piece = board[(int)to[0]][(int)to[1] - 48];
   if (piece[0] == 'W' || piece[1] != 'W')
      return false;
   return true;
}
bool Player1::queen(string from, string to) // Finished
{
   return rook(from, to) && bishop(from, to);
}
bool Player1::canMove(string to, string from)
{
   string piece = board[from[0]][from[1] - 48];
   cout << piece << endl;
   switch (piece[0])
   {
   case 'K':
      return king(from, to);
   case 'Q':
      return queen(from, to);
   }
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
   cout << "Error!!";
   return false;
}
boardType Player1::move(string from, string to)
{
   board[to[0]][to[1] - 48] = board[from[0]][from[1] - 48];
   board[from[0]][from[1] - 48] = "  ";
   return board;
}
map<string, int> Player1::countPiece()
{
   map<string, int> piece;
   for (auto itr : board)
   {
      for (int i = 1; i < 9; i++)
         piece[itr[i]]++;
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
boardType Player1::turn(boardType currentBoard)
{
   setBoard(currentBoard);
   cout << "Enter the position of the piece to move: ";
   string from;
   cin >> from;
   string piece;
   while ((piece = isValid(from, currentBoard, 1)) == "-1")
   {
      cout << "Invalid input! Enter a valid cell position (e.g., A2): ";
      cin >> from;
   }
   cout << "Enter the position where you want to move your";
   switch (piece[0])
   {
   case 'K':
      cout << " King";
      goto print;
   case 'Q':
      cout << " Queen";
      goto print;
   }
   switch (piece[1])
   {
   case 'P':
      cout << " Pawn";
      goto print;
   case 'R':
      cout << " Rook";
      goto print;
   case 'K':
      cout << " Knight";
      goto print;
   case 'B':
      cout << " Bishop";
      goto print;
   }
print:
   cout << ": ";
   string to;
   cin >> to;
   while (!isValid(to, from) || !canMove(to, from))
   {
      cout << "Invalid input! Enter a valid cell position or check if the piece can move to the specified location: " << endl;
      cin >> to;
   }
   return move(from, to);
}