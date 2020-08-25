#include <iostream>
#include <vector>
using namespace std;

void printboard (vector <vector <int> > &board);

int main (int arg, char** argv)
{
  int rows = 4;
  int cols = 4;
  vector <vector <int> > board (rows, vector<int> (cols));

  int k = 1;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
    {
      board[i][j] = k;
      k++;
    }
  board[3][3] = 0;

  printboard(board);
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
