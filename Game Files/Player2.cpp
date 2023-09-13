class Player2 : public Driver
{
protected:
   int **board;
   int turns;

public:
   Player2(int **);
   void setBoard(int **);
   int **turn(int **);
   bool hasWon();
};
Player2::Player2(int **board)
{
   turns = 0;
   setBoard(board);
}
void Player2::setBoard(int **board)
{
   this->board = board;
}
bool Player2::hasWon()
{
   std::map<int, int> pieces = countpieces(board);
   if (pieces[6] == 0)
      return true;
   return false;
}
int **Player2::turn(int **currentBoard)
{
   turns++;
   setBoard(currentBoard);
   return driver(2, currentBoard, turns);
}