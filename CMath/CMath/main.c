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

#define X_SIZE 80
#define Y_SIZE 29

void init_window();
void set_window_size(int width, int height);
void set_buffer_size(int width, int height);
void gotoxy(int x, int y);
void wherexy(int *x, int *y);
void set_color(long color);

void init_matrix(int matrix[X_SIZE][Y_SIZE]);
void show_matrix(int matrix[X_SIZE][Y_SIZE]);
void fill_matrix(int matrix[X_SIZE][Y_SIZE]);

main()
{
	int matrix[X_SIZE][Y_SIZE];
	bool running;
	char input[80];
	int len;
	int ch;

	init_window();

	fill_matrix(matrix);
	show_matrix(matrix);

	len = 0;
	running = true;
	while (running) {
		while (!kbhit()) {
		}

		ch = getch();
		if (ch == 13) {
			/* enter key */
			input[len] = '\0';
			if (!strcmp(input, "exit")) {
				running = false;
			}
			for (len = 0; len < 79; len++)
				input[len] = ' ';
			input[len] = '\0';
			gotoxy(0, 29);
			printf("%s", input);
			gotoxy(0, 29);
			strcpy(input, "");
			len = 0;
		} else if (ch == 27) {
			/* escape key */
			running = false;
		} else if (ch == 8) {
			/* backspace */
			printf("\b \b");
			if (len > 0)
				len--;
		} else {
			if (len < 79) {
				if (isalpha(ch)) {
					input[len++] = ch;
					printf("%c", (char)ch);
				}
			}
		}
	}
}

void init_window()
{
	set_buffer_size(80, 30);
	set_window_size(80, 30);
}

void set_window_size(int width, int height)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	SMALL_RECT srctWindow;

	srctWindow.Left = 0;
	srctWindow.Top = 0;
	srctWindow.Bottom = height - 1;
	srctWindow.Right = width - 1;
	
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &srctWindow);
}

void set_buffer_size(int width, int height)
{
	COORD size;

	size.X = width;
	size.Y = height;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);
}

void gotoxy(int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coord;
	HANDLE hStdOutput;

	hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdOutput, &csbi);
	if (x < 0 || x > csbi.dwSize.X ||
		y < 0 || y > csbi.dwSize.Y)
	{
		/* out of borders */
		return;
	}

	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hStdOutput, coord);
}

void wherexy(int *x, int *y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	*x = csbi.dwCursorPosition.X;
	*y = csbi.dwCursorPosition.Y;
}

void set_color(long color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void init_matrix(int matrix[X_SIZE][Y_SIZE])
{
	int x, y;

	for (y = 0; y < Y_SIZE; y++) {
		for (x = 0; x < X_SIZE; x++) {
			matrix[x][y] = 0;
		}
	}
}

void show_matrix(int matrix[X_SIZE][Y_SIZE])
{
	int x, y;

	for (y = 0; y < Y_SIZE; y++) {
		for (x = 0; x < X_SIZE; x++) {
			gotoxy(x, y);
			printf("%d", matrix[x][y]);
		}
	}
}

void fill_matrix(int matrix[X_SIZE][Y_SIZE])
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
