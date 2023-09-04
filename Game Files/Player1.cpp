class Player1 : public Driver
{
protected:
   boardType board;

public:
   Player1(boardType);
   boardType move(std::string, std::string);
   void setBoard(boardType);
   boardType turn(boardType);
   bool hasWon();
};
Player1::Player1(boardType board)
{
   setBoard(board);
}
void Player1::setBoard(boardType board)
{
   this->board = board;
}
bool Player1::hasWon()
{
   std::map<std::string, int> pieces = countpieces(board);
   if (pieces["KB"] == 0)
      return true;
   return false;
}
boardType Player1::turn(boardType currentBoard)
{
   setBoard(currentBoard);
   return driver(1, currentBoard);
}