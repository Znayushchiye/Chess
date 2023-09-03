class Valid : public ChessPieces
{
protected:
   string validPos(string);
   string isValid(string, boardType, int);
   bool isValid(string, string, boardType, int);
   bool canMove(string, string, boardType, int);
};
string Valid::validPos(string str)
{
   string temp = str;
   str = "";
   // Make all the characters as UpperCase
   for (char ch : temp)
      str += toupper(ch);
   char ch;
   temp = "";
   for (int i = 0; (ch = str[i]) != '\0'; i++)
   {
      // If the character is not a number or alphabet, ignore it.
      if (!isalnum(ch))
         continue;
      // If the character is an alphabet or number, check if it lies in range.
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
   if (!isalpha(str[0]))
      swap(str[0], str[1]);
   return str;
}
string Valid::isValid(string from, boardType board, int turn) // Finished
{
   string temp = validPos(from);
   if (temp == "-1")
      return "-1";
   string piece = board[(int)temp[0]][(int)temp[1] - 48];
   switch (turn)
   {
   case 1:
      if (piece == "  " || piece[0] == 'B' || piece == "KB" || piece == "QB")
         return "-1";
      break;
   case 2:
      if (piece == "  " || piece[0] == 'W' || piece[1] == 'W')
         return "-1";
      break;
   }
   return piece;
}
bool Valid::isValid(string to, string from, boardType board, turn) // Finished
{
   string temp = validPos(to);
   if (temp == "-1")
      return false;
   to = temp;
   if (from == to)
      return false;
   return canMove(to, from, board, turn);
}
bool Valid::canMove(string to, string from, boardType board, int turn)
{
   string piece = board[from[0]][from[1] - 48];
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
   cout << "Error!!";
   return false;
}