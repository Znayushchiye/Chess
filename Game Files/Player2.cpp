class Player2 : public Driver
{
protected:
   boardType board;

public:
   Player2(boardType);
   boardType move(std::string, std::string);
   void setBoard(boardType);
   boardType turn(boardType);
   bool hasWon();
};
Player2::Player2(boardType board)
{
   setBoard(board);
}
void Player2::setBoard(boardType board)
{
   this->board = board;
}
bool Player2::hasWon()
{
   std::map<std::string, int> pieces = countpieces(board);
   if (pieces["KW"] == 0)
      return true;
   return false;
}
boardType Player2::turn(boardType currentBoard)
{
   setBoard(currentBoard);
   return driver(2, currentBoard);
}