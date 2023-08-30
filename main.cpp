#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;
const int width = 40, height = 20;
int x, y, fruitx, fruity, score = 0, nTail = 0;
int tailx[100], taily[100];
bool gameOver;
enum Direction { STOP = 0, UP, RIGHT, LEFT, DOWN };
Direction dir;

void setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitx = rand() % width;
	fruity = rand() % height;
}

void draw()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	for (int i = 0; i < width; i++)
	{
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height - 2; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
				cout << '#';
			}
			else
			{
				if (i == y && j == x)cout << 'O';
				else if (i == fruity && j == fruitx) cout << 'X';
				else
				{
					bool print = false;
					for (int k = 0; k < nTail; k++)
					{
						if (tailx[k] == j && taily[k] == i)
						{
							cout << "o";
							print = true;
						}
					}
					if (!print)cout << " ";
				}
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score:  " << score << endl;
}

void logic()
{
	int prevX = tailx[0];
	int prevY = taily[0];
	int prev2X, prev2Y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailx[i];
		prev2Y = taily[i];
		tailx[i] = prevX;
		taily[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case STOP:
		break;
	case UP:
		y--;
		break;
	case RIGHT:
		x++;
		break;
	case LEFT:
		x--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x == -1 || y == - 2 || x == width  || y == height )gameOver = true;

	if (x == fruitx && y == fruity)
	{
		score += 100;
		fruitx = rand() % width;
		fruity = rand() % height;
		nTail++;
	}
}

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameOver = true;
		default:
			break;
		}
	}
}

int main()
{
	setup();
	while (!gameOver)
	{
		input();
		draw();
		logic();
		Sleep(150);
	};
	return 0;
}
