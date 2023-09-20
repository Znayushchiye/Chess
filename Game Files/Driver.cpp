#include "Valid.cpp"
class Driver : public Valid
{
protected:
   int **driver(int, int **, int);
   int **move(string, string, int **);
};

int **Driver::driver(int turn, int **currentBoard, int turns)
{
inputFrom:
   cout << "   From: ";
   string from;
   cin >> from;
   if (from == "end")
   {
      return currentBoard;
   }
   int piece;
   while (!(piece = isValid(from, currentBoard, turn)))
   {
      cout << "   Invalid input! Enter a valid cell position: ";
      cin >> from;
   }
   cout << "   Chosen piece:";
   switch (abs(piece))
   {
   case 6:
      cout << " King";
      goto print;
   case 5:
      cout << " Queen";
      goto print;
   case 4:
      cout << " Bishop";
      goto print;
   case 3:
      cout << " Knight";
      goto print;
   case 2:
      cout << " Rook";
      goto print;
   case 1:
      cout << " Pawn";
      goto print;
   }
print:
   cout << "\n   To: ";
   string to;
   cin >> to;
   if (to == "end")
   {
      return currentBoard;
   }
   if (to == "back")
   {
      goto inputFrom;
   }
   while (!isValid(to, from, currentBoard, turn, turns))
   {
      cout << "   Invalid input! Check if your piece can move to the specified location: ";
      cin >> to;
      if (to == "end")
      {
         return currentBoard;
      }
      if (to == "back")
      {
         goto inputFrom;
      }
   }
   return move(from, to, currentBoard);
}
int **Driver::move(string from, string to, int **board)
{
   board[to[0] - 65][to[1] - 48] = board[from[0] - 65][from[1] - 48];
   board[from[0] - 65][from[1] - 48] = 0;
   return board;
}