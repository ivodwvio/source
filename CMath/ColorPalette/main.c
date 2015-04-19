#include <stdio.h>
#include <Windows.h>

void SetColor(long color);

main()
{
	int i;

	for (i = 0; i < 256; i++) {
		SetColor(i);
		if (i == 0)
			printf("%c ", '&');
		else if (i % 10 == 0)
			printf("\n");
		else
			printf("%c ", '&');
	}
}

void SetColor(long color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
