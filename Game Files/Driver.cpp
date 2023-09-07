#include "Valid.cpp"
class Driver : public Valid
{
protected:
   int **driver(int, int **);
   int **move(std::string, std::string, int **);
};

int **Driver::driver(int turn, int **currentBoard)
{
   std::cout << "   From: ";
   std::string from;
   std::cin >> from;
   int piece;
   while (!(piece = isValid(from, currentBoard, turn)))
   {
      std::cout << "   Invalid input! Enter a valid cell position: ";
      std::cin >> from;
   }
   std::cout << "   Chosen piece:";
   switch (abs(piece))
   {
   case 6:
      std::cout << " King";
      goto print;
   case 5:
      std::cout << " Queen";
      goto print;
   case 4:
      std::cout << " Bishop";
      goto print;
   case 3:
      std::cout << " Knight";
      goto print;
   case 2:
      std::cout << " Rook";
      goto print;
   case 1:
      std::cout << " Pawn";
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
int **Driver::move(std::string from, std::string to, int **board)
{
   board[to[0] - 65][to[1] - 48] = board[from[0] - 65][from[1] - 48];
   board[from[0] - 65][from[1] - 48] = 0;
   return board;
}