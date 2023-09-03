class Player2 : public Valid
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
   Player2(boardType);
   boardType move(string, string);
   void setBoard(boardType);
   boardType turn(boardType);
   bool hasWon();
};
Player2::Player2(boardType board)
{
   setBoard(board);
}
void Player2::setBoard(boardType board)
{
   this->board = board;
}
bool Player2::pawn(string from, string to)
{
   if (((to[0] != from[0] + 1) || (to[1] != from[1])) && ((to[0] != from[0] + 2) || (to[1] != from[1])) && ((to[0] != from[0] + 1) || (abs(to[1] - from[1]) != 1)))
      return false;
   string piece = board[(int)to[0]][(int)to[1] - 48];
   if ((to[0] == from[0] + 1) && (abs(to[1] - from[1]) == 1) && (piece[0] != 'W') && (piece[1] != 'W'))
      return false;
   if ((from[1] == to[1]) && (piece != "  "))
      return false;
   if ((to[0] == from[0] + 2) && (board[to[0] - 1][to[1] - 48] != "  "))
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
         string pos = board[to[0]][i - 48];
         if (pos != "  ")
            return false;
      }
   else
      for (char i = from[0]; i < to[0]; i++)
      {
         string pos = board[i][to[1] - 48];
         if (pos != "  ")
            return false;
      }
   string piece = board[to[0]][to[1] - 48];
   if (piece[0] != 'W' && piece[1] != 'W' && piece != "  ")
      return false;
   return true;
}
bool Player2::bishop(string from, string to)
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
   if (piece[0] != 'W' && piece[1] != 'W' && piece != "  ")
      return false;
   return true;
}
bool Player2::knight(string from, string to)
{
   if ((abs(from[0] - to[0]) > 1 && abs(from[1] - to[1]) != 2) || (abs(from[1] - to[1]) > 1 && abs(from[0] - to[0]) != 2))
      return false;
   string piece = board[to[0]][to[1] - 48];
   if (piece[0] != 'W' && piece[1] != 'W' && piece != "  ")
      return false;
   return true;
}
bool Player2::king(string from, string to)
{
   if ((abs(from[0] - to[0]) > 1) || (abs(from[1] - to[1]) > 1))
      return false;
   string piece = board[to[0]][to[1] - 48];
   if (piece[0] != 'W' && piece[1] != 'W' && piece != "  ")
      return false;
   return true;
}
bool Player2::queen(string from, string to)
{
   return rook(from, to) && bishop(from, to);
}
boardType Player2::move(string from, string to)
{
   board[to[0]][to[1] - 48] = board[from[0]][from[1] - 48];
   board[from[0]][from[1] - 48] = "  ";
   return board;
}
map<string, int> Player2::countPiece()
{
   map<string, int> piece;
   for (auto itr : board)
   {
      for (int i = 1; i < 9; i++)
         piece[itr[i]]++;
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
boardType Player2::turn(boardType currentBoard)
{
   setBoard(currentBoard);
   cout << "Enter the position of the piece to move: ";
   string from;
   cin >> from;
   string piece;
   while ((piece = isValid(from, currentBoard, 2)) == "-1")
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
   while (!isValid(to, from, currentBoard, 2))
   {
      cout << "Invalid input! Enter a valid cell position or check if the piece can move to the specified location: ";
      cin >> to;
   }
   return move(from, to);
}