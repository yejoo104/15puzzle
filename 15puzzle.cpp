#include <iostream>
#include <vector>
#include <random>
using namespace std;

void printboard (vector <vector <int> > &board);
vector <vector <int> > makeboard(int rows, int cols);

int main (int arg, char** argv)
{
  int rows = 4;
  int cols = 4;
  vector <vector <int> > board (rows, vector<int> (cols));

  board = makeboard(rows, cols);

  printboard(board);

  // Find where zero is (Try and make this more efficient)
  int blankrow;
  int blankcol;
  for (int i = 0; i < board.size(); i++)
    for (int j = 0; j < board[i].size(); j++)
      if (board[i][j] == 0)
      {
        blankrow = i;
        blankcol = j;
      }

  while (true)
  {
    cout << "Use Arrow Keys to Move.";
    int a = getchar();
    int b = getchar();
    int c = getchar();
    int d = getchar();

    if (a != 27 || b != 91 || d != 10) continue;
    if (c < 65 || c > 68) continue;

    int changerow = 0;
    int changecol = 0;

    if (c == 65) changerow = 1;
    if (c == 66) changerow = -1;
    if (c == 67) changecol = -1;
    if (c == 68) changecol = 1;

    // If Direction is Out of Array, CONTINUE
    if (blankrow + changerow < 0 || blankrow + changerow >= board.size()) continue;
    if (blankcol + changecol < 0 || blankcol + changecol >= board[0].size()) continue;

    // Move the blank cell and update row/cell
    board[blankrow][blankcol] = board[blankrow + changerow][blankcol + changecol];
    blankrow = blankrow + changerow;
    blankcol = blankcol + changecol;
    board[blankrow][blankcol] = 0;

    printboard(board);
  } 
}

void printboard (vector <vector <int> > &board)
{
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
    {
      if (board[i][j] == 0) cout << "_\t";
      else cout << board[i][j] << "\t";
    }
    cout << endl;
  }
}

vector <vector <int> > makeboard(int rows, int cols)
{
  // Make an Entirely Solved Board
  vector <vector <int> > board(rows, vector<int>(cols));
  int num = 0;
  for (int i = 0; i < board.size(); i++)
    for (int j = 0; j < board[i].size(); j++)
    {
      num++;
      board[i][j] = num;
    }

  int blankrow = rows - 1;
  int blankcol = cols - 1;
  board[blankrow][blankcol] = 0;

  // Make Random generator
  random_device device;
  mt19937 generator(device());
  uniform_int_distribution<> directiondis(1, 4);

  // Swap for sufficient turns
  int trials = pow(2, rows + cols);
  for (int i = 0; i < trials; i++)
  {
    int direction = directiondis(generator);
    int changerow = 0;
    int changecol = 0;

    // Swap UP
    if (direction == 1) changerow = -1;
    // Swap RIGHT
    if (direction == 2) changecol = 1;
    // Swap DOWN
    if (direction == 3) changerow = 1;
    // Swap LEFT
    if (direction == 4) changecol = -1;

    // If Direction is Out of Array, CONTINUE
    if (blankrow + changerow < 0 || blankrow + changerow >= board.size()) continue;
    if (blankcol + changecol < 0 || blankcol + changecol >= board[0].size()) continue;

    // Do the SWAP and update where blank row / col is
    board[blankrow][blankcol] = board[blankrow + changerow][blankcol + changecol];
    blankrow = blankrow + changerow;
    blankcol = blankcol + changecol;
    board[blankrow][blankcol] = 0;
  }

  return board;
}
