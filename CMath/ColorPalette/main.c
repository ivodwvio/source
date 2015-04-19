#include <stdio.h>
#include <Windows.h>

void SetColor(long color);

main()
{
	int i;

	for (i = 0; i < 256; i++) {
		SetColor(i);
		if (i == 0)
			printf("%d = %c ", i, '&');
		else if (i % 10 == 0)
			printf("\n");
		else
			printf("%d = %c ", i, '&');
	}
}

void SetColor(long color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
