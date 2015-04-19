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

#define MATRIX_X_SIZE 80
#define MATRIX_Y_SIZE 29

#define KEY_ENTER 13
#define KEY_ESCAPE 27
#define KEY_BACKSPACE 8
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

typedef struct _Element {
	int id;
} Element;

void SetWindowSize(int width, int height);
void SetBufferSize(int width, int height);
bool GotoXY(int x, int y);
bool IsValidPosition(int x, int y);
void WhereXY(int *x, int *y);
void SetColor(long color);

void InitMatrix(Element matrix[MATRIX_X_SIZE][MATRIX_Y_SIZE]);
void FillMatrix(Element matrix[MATRIX_X_SIZE][MATRIX_Y_SIZE]);
void ShowMatrix(Element matrix[MATRIX_X_SIZE][MATRIX_Y_SIZE]);

void InitWindow();
void CleanWindow();
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

Element matrix[MATRIX_X_SIZE][MATRIX_Y_SIZE];
bool running;
int ch;

typedef enum {
	EMPTY_SPACE_ID,
	WALL_ID,
	HEARTS_ID,
	SPADES_ID,
	DIAMONDS_ID,
	CLUBS_ID
};
#define ELEMENTS_COUNT 6

char sprites[] = {' ', 219, 3, 6, 4, 5};
char colors[] = {0, 119, 12, 9, 12, 9};

main()
{
	InitWindow();

	InitMatrix(matrix);
	ShowMatrix(matrix);
	system("pause>nul");
	FillMatrix(matrix);
	ShowMatrix(matrix);

	Run();

	CleanWindow();
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
		case KEY_ENTER:
			OnEnter();
			break;
		case KEY_ESCAPE:
			OnEscape();
			break;
		case KEY_BACKSPACE:
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

void CleanWindow()
{
	SetColor(7);
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

void InitMatrix(Element matrix[MATRIX_X_SIZE][MATRIX_Y_SIZE])
{
	int x, y;

	for (x = 0; x < MATRIX_X_SIZE; x++) {
		for (y = 0; y < MATRIX_Y_SIZE; y++) {
			matrix[x][y].id = EMPTY_SPACE_ID;
		}
	}
}

void FillMatrix(Element matrix[MATRIX_X_SIZE][MATRIX_Y_SIZE])
{
	int x, y;
	int colorID;
	char spriteID;

	srand(time(NULL));

	for (y = 0; y < MATRIX_Y_SIZE; y++) {
		for (x = 0; x < MATRIX_X_SIZE; x++) {
			matrix[x][y].id = rand() % ELEMENTS_COUNT;
		}
	}
}

void ShowMatrix(Element matrix[MATRIX_X_SIZE][MATRIX_Y_SIZE])
{
	int x, y;

	for (y = 0; y < MATRIX_Y_SIZE; y++) {
		for (x = 0; x < MATRIX_X_SIZE; x++) {
			GotoXY(x, y);
			SetColor(colors[matrix[x][y].id]);
			printf("%c", sprites[matrix[x][y].id]);
		}
	}
}
