#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>

#ifndef __cplusplus__
typedef unsigned char bool;
#define true 1
#define false 0
#endif

#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 30

#define X_SIZE 80
#define Y_SIZE 29

#define ENTER 13
#define ESCAPE 27
#define BACKSPACE 8
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void SetWindowSize(int width, int height);
void SetBufferSize(int width, int height);
bool GotoXY(int x, int y);
bool IsValidPosition(int x, int y);
void WhereXY(int *x, int *y);
void SetColor(long color);

void InitMatrix(int matrix[X_SIZE][Y_SIZE]);
void ShowMatrix(int matrix[X_SIZE][Y_SIZE]);
void FillMatrix(int matrix[X_SIZE][Y_SIZE]);

void InitWindow();
void KeyInput(int ch);
void Run();

void OnEnter();
void OnEscape();
void OnBackspace();
void OnKeyUp();
void OnKeyDown();
void OnKeyLeft();
void OnKeyRight();
void OnDefault();

bool MoveCursor(int x, int y);

int matrix[X_SIZE][Y_SIZE];
bool running;
int ch;

main()
{
	InitWindow();

	FillMatrix(matrix);
	ShowMatrix(matrix);

	Run();
}

void Run()
{
	running = true;
	while (running) {
		while (!kbhit()) {
		}
		ch = getch();
		KeyInput(ch);
	}
}

bool MoveCursor(int x, int y)
{
	int oldx, oldy;

	WhereXY(&oldx, &oldy);
	return GotoXY(oldx+x, oldy+y);
}

void OnEnter()
{
}

void OnEscape()
{
	running = false;
}

void OnBackspace()
{
}

void OnKeyUp()
{
	MoveCursor(0, -1);
}

void OnKeyDown()
{
	MoveCursor(0, 1);
}

void OnKeyLeft()
{
	MoveCursor(-1, 0);
}

void OnKeyRight()
{
	MoveCursor(1, 0);
}

void OnDefault()
{
}

void KeyInput(int ch)
{
	switch (ch) {
		case ENTER:
			OnEnter();
			break;
		case ESCAPE:
			OnEscape();
			break;
		case BACKSPACE:
			OnBackspace();
			break;
		case KEY_UP:
			OnKeyUp();
			break;
		case KEY_DOWN:
			OnKeyDown();
			break;
		case KEY_LEFT:
			OnKeyLeft();
			break;
		case KEY_RIGHT:
			OnKeyRight();
			break;
		default:
			OnDefault();
			break;
	}
}

void InitWindow()
{
	SetBufferSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void SetWindowSize(int width, int height)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	SMALL_RECT srctWindow;

	srctWindow.Left = 0;
	srctWindow.Top = 0;
	srctWindow.Bottom = height - 1;
	srctWindow.Right = width - 1;
	
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &srctWindow);
}

void SetBufferSize(int width, int height)
{
	COORD size;

	size.X = width;
	size.Y = height;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);
}

bool GotoXY(int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coord;
	HANDLE hStdOutput;

	hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdOutput, &csbi);
	
	if (!IsValidPosition(csbi.dwSize.X, csbi.dwSize.Y))
		return false;

	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hStdOutput, coord);
	return true;
}

bool IsValidPosition(int x, int y)
{
	if (x < 0 || x > WINDOW_WIDTH ||
		y < 0 || y > WINDOW_HEIGHT)
	{
		/* out of borders */
		return false;
	}

	return true;
}

void WhereXY(int *x, int *y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	*x = csbi.dwCursorPosition.X;
	*y = csbi.dwCursorPosition.Y;
}

void SetColor(long color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void InitMatrix(int matrix[X_SIZE][Y_SIZE])
{
	int x, y;

	for (y = 0; y < Y_SIZE; y++) {
		for (x = 0; x < X_SIZE; x++) {
			matrix[x][y] = 0;
		}
	}
}

void ShowMatrix(int matrix[X_SIZE][Y_SIZE])
{
	int x, y;

	for (y = 0; y < Y_SIZE; y++) {
		for (x = 0; x < X_SIZE; x++) {
			GotoXY(x, y);
			SetColor(matrix[x][y]);
			printf("%d", matrix[x][y]);
		}
	}
}

void FillMatrix(int matrix[X_SIZE][Y_SIZE])
{
	int x, y;
	int r;

	srand(time(NULL));

	for (y = 0; y < Y_SIZE; y++) {
		for (x = 0; x < X_SIZE; x++) {
			r = rand() % 10;
			matrix[x][y] = r;
		}
	}
}
