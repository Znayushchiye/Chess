class Player1 : public Driver
{
protected:
   int **board;

public:
   Player1(int **);
   void setBoard(int **);
   int **turn(int **);
   bool hasWon();
};
Player1::Player1(int **board)
{
   setBoard(board);
}
void Player1::setBoard(int **board)
{
   this->board = board;
}
bool Player1::hasWon()
{
   std::map<int, int> pieces = countpieces(board);
   if (pieces[-6] == 0)
      return true;
   return false;
}
int **Player1::turn(int **currentBoard)
{
   setBoard(currentBoard);
   return driver(1, currentBoard);
}