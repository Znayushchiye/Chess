#include <iostream>
int main()
{
   int **board = new int *[5];
   int count = 1;
   for (int i = 0; i < 5; i++)
   {
      board[i] = new int[5];
      for (int j = 0; j < 5; j++)
      {
         board[i][j] = count++;
      }
   }
   for (int i = 0; i < 5; i++)
   {
      for (int j = 0; j < 5; j++)
      {
         std::cout << board[i][j] << " ";
      }
      std::cout << "\n";
   }
   return 0;
}