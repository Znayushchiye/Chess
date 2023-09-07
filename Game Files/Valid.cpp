#include "ChessPieces.cpp"
class Valid : public ChessPieces
{
protected:
   std::string validPos(std::string);
   int isValid(std::string, int **, int);
   bool isValid(std::string, std::string, int **, int);
   bool canMove(std::string, std::string, int **, int);
   std::map<int, int> countpieces(int **);
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
int Valid::isValid(std::string from, int **board, int turn) // Finished
{
   from = validPos(from);
   if (from == "-1")
      return 0;
   int piece = board[from[0] - 65][from[1] - 48];
   if (piece == 0)
      return 0;
   switch (turn)
   {
   case 1:
      if (piece < 0)
         return 0;
      break;
   case 2:
      if (piece > 0)
         return 0;
      break;
   }
   return piece;
}
bool Valid::isValid(std::string to, std::string from, int **board, int turn) // Finished
{
   to = validPos(to);
   if (to == "-1")
      return 0;
   if (from == to)
      return 0;
   return canMove(to, from, board, turn);
}
bool Valid::canMove(std::string to, std::string from, int **board, int turn)
{
   int piece = board[from[0] - 65][from[1] - 48];
   switch (abs(piece))
   {
   case 6:
      return king(from, to, board, turn);
   case 5:
      return queen(from, to, board, turn);
   case 1:
      return pawn(from, to, board, turn);
   case 2:
      return rook(from, to, board, turn);
   case 3:
      return knight(from, to, board, turn);
   case 4:
      return bishop(from, to, board, turn);
   }
   std::cout << "Error!!";
   return false;
}
std::map<int, int> Valid::countpieces(int **board)
{
   std::map<int, int> piece;
   for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
         piece[board[i][j]]++;
   return piece;
}