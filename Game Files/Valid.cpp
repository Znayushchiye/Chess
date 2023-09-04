class Valid : public ChessPieces
{
protected:
   std::string validPos(std::string);
   std::string isValid(std::string, boardType, int);
   bool isValid(std::string, std::string, boardType, int);
   bool canMove(std::string, std::string, boardType, int);
   std::map<std::string, int> countpieces(boardType);
};
std::string Valid::validPos(std::string str)
{
   std::string temp = "";
   char ch;
   for (int i = 0; (ch = str[i]) != '\0'; i++)
   {
      // If the character is not a number or alphabet, ignore it.
      if (!isalnum(ch))
         continue;
      // Make all characters uppercase
      ch = toupper(ch);
      // If the character is alphanumeric, check if it lies in range.
      if ((ch < 'A' || ch > 'H') && (ch < '1' || ch > '8'))
         return "-1";
      temp += ch;
   }
   // If the cell position is not eqaul to 2, return false equivalent.
   if (temp.length() != 2)
      return "-1";
   str = temp;
   // Check if both the characters are alphabets or digits.
   if ((isalpha(str[0]) && isalpha(str[1])) || (isdigit(str[0]) && isdigit(str[1])))
      return "-1";
   // Make the the cell position of the form A6, H2 etc.
   if (isdigit(str[0]))
      std::swap(str[0], str[1]);
   return str;
}
std::string Valid::isValid(std::string from, boardType board, int turn) // Finished
{
   from = validPos(from);
   if (from == "-1")
      return "-1";
   std::string piece = board[from[0]][from[1] - 48];
   if (piece == "  ")
      return "-1";
   switch (turn)
   {
   case 1:
      if (piece[0] == 'B' || piece == "KB" || piece == "QB")
         return "-1";
      break;
   case 2:
      if (piece[0] == 'W' || piece[1] == 'W')
         return "-1";
      break;
   }
   return piece;
}
bool Valid::isValid(std::string to, std::string from, boardType board, int turn) // Finished
{
   to = validPos(to);
   if (to == "-1")
      return false;
   if (from == to)
      return false;
   return canMove(to, from, board, turn);
}
bool Valid::canMove(std::string to, std::string from, boardType board, int turn)
{
   std::string piece = board[from[0]][from[1] - 48];
   switch (piece[0])
   {
   case 'K':
      return king(from, to, board, turn);
   case 'Q':
      return queen(from, to, board, turn);
   }
   switch (piece[1])
   {
   case 'P':
      return pawn(from, to, board, turn);
   case 'R':
      return rook(from, to, board, turn);
   case 'B':
      return bishop(from, to, board, turn);
   case 'K':
      return knight(from, to, board, turn);
   }
   std::cout << "Error!!";
   return false;
}
std::map<std::string, int> Valid::countpieces(boardType board)
{
   std::map<std::string, int> piece;
   for (int i = 65; i < 73; i++)
      for (int j = 1; j < 9; j++)
         piece[board[i][j]]++;
   return piece;
}

class Driver : public Valid
{
protected:
   boardType driver(int, boardType);
   boardType move(std::string, std::string, boardType);
};

boardType Driver::driver(int turn, boardType currentBoard)
{
   std::cout << "   From: ";
   std::string from;
   std::cin >> from;
   std::string piece;
   while ((piece = isValid(from, currentBoard, turn)) == "-1")
   {
      std::cout << "   Invalid input! Enter a valid cell position: ";
      std::cin >> from;
   }
   std::cout << "   Chosen piece:";
   switch (piece[0])
   {
   case 'K':
      std::cout << " King";
      goto print;
   case 'Q':
      std::cout << " Queen";
      goto print;
   }
   switch (piece[1])
   {
   case 'P':
      std::cout << " Pawn";
      goto print;
   case 'R':
      std::cout << " Rook";
      goto print;
   case 'K':
      std::cout << " Knight";
      goto print;
   case 'B':
      std::cout << " Bishop";
      goto print;
   }
print:
   std::cout << "\n   To: ";
   std::string to;
   std::cin >> to;
   while (!isValid(to, from, currentBoard, turn))
   {
      std::cout << "   Invalid input! Check if your piece can move to the specified location: ";
      std::cin >> to;
   }
   return move(from, to, currentBoard);
}
boardType Driver::move(std::string from, std::string to, boardType board)
{
   board[to[0]][to[1] - 48] = board[from[0]][from[1] - 48];
   board[from[0]][from[1] - 48] = "  ";
   return board;
}