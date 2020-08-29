#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace sf;
using namespace std;

vector <vector <int> > makeboard(int rows, int cols);

int main (int arg, char** argv)
{
  // Take input for row numbers and column numbers
  cout << "Number of rows? ";
  int rows;
  cin >> rows;
  cout << "Number of columns? ";
  int cols;
  cin >> cols;

  // Make Board
  vector <vector <int> > board (rows, vector<int> (cols));
  board = makeboard(rows, cols);

  // Take Input Image
  Texture t;
  t.loadFromFile("moongchi1.JPG");
  Sprite s(t);

  // Decide sizes for Puzzle
  int imagewidth = s.getLocalBounds().width;
  int imageheight = s.getLocalBounds().height;
  float width = imagewidth / cols;
  float height = imageheight / rows;
  RenderWindow app(VideoMode(imagewidth, imageheight), "Puzzle");

  // Winner Message
  Font font;
  font.loadFromFile("Ka Blam.ttf");
  Text winner;
  winner.setFont(font);
  winner.setString("YOU WIN");
  winner.setCharacterSize(imageheight / 10);
  winner.setFillColor(Color::White);
  winner.setStyle(Text::Bold);
  winner.setPosition(imagewidth / 2.0f, imageheight / 2.0f);
  winner.setOrigin(winner.getLocalBounds().width / 2.0f, winner.getLocalBounds().height / 2.0f);

  // Find where zero is and count how many cells are aligned
  int blankrow;
  int blankcol;
  int count = 0;
  for (int i = 0; i < board.size(); i++)
    for (int j = 0; j < board[i].size(); j++)
    {
      if (board[i][j] == 0)
      {
        blankrow = i;
        blankcol = j;
      }

      if (board[i][j] == i * cols + j + 1) count++;
    }

  // Variable for whether you've won
  bool won = false;

  while (app.isOpen())
  {
    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed) app.close();

      if (!won && e.type == Event::KeyPressed)
      {
        int changerow = 0;
        int changecol = 0;

        if (e.key.code == Keyboard::Up) changerow = 1;
        else if (e.key.code == Keyboard::Down) changerow = -1;
        else if (e.key.code == Keyboard::Left) changecol = 1;
        else if (e.key.code == Keyboard::Right) changecol = -1;
        else continue;

        // If Direction is Out of Array, CONTINUE
        if (blankrow + changerow < 0 || blankrow + changerow >= board.size()) continue;
        if (blankcol + changecol < 0 || blankcol + changecol >= board[0].size()) continue;

        // Move the blank cell and update row/cell as well as count
        int newrow = blankrow + changerow;
        int newcol = blankcol + changecol;
        if (board[newrow][newcol] == newrow * cols + newcol + 1) count--;
        if (board[newrow][newcol] == blankrow * cols + blankcol + 1) count++;
        board[blankrow][blankcol] = board[newrow][newcol];
        blankrow = newrow;
        blankcol = newcol;
        board[blankrow][blankcol] = 0;
      }
    }

    app.clear(Color::White);

    for (int i = 0; i < board.size(); i++)
      for (int j = 0; j < board[i].size(); j++)
      {
        if (board[i][j] == 0) continue;
        else s.setTextureRect(IntRect(width * ((board[i][j] + cols - 1) % cols), height * ((board[i][j] - 1) / cols), width, height));
        s.setPosition(j * width, i * height);
        app.draw(s);
      }

    if (won) app.draw(winner);
    app.display();

    if (count >= rows * cols - 1) won = true;
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
