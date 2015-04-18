#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define X_SIZE 20
#define Y_SIZE 10

void init_matrix(int matrix[X_SIZE][Y_SIZE]);
void show_matrix(int matrix[X_SIZE][Y_SIZE]);
void fill_matrix(int matrix[X_SIZE][Y_SIZE]);

main()
{
	int matrix[X_SIZE][Y_SIZE];

	init_matrix(matrix);
	show_matrix(matrix);
	fill_matrix(matrix);
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
			printf("%d", matrix[x][y]);
		}
		printf("\n");
	}
}

void fill_matrix(int matrix[X_SIZE][Y_SIZE])
{
}
