#include <iostream>
#include <map>
#include <vector>
#define boardType vector<vector<string>>
using namespace std;
string validPos(string str)
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
   // Make the the cell position of the form A6, H2 etc.
   if (!isalpha(str[0]))
      swap(str[0], str[1]);
   return str;
}
string isValid(string from, boardType board, int turn) // Finished
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
   case 2:
      if (piece == "  " || piece[0] == 'W' || piece[1] == 'W')
         return "-1";
   }
   return piece;
}
bool isValid(string to, string from) // Finished
{
   string temp = validPos(to);
   if (temp == "-1")
      return false;
   to = temp;
   if (from == to)
      return false;
   cout << "CanMove called";
   return true;
}