#include <stdio.h>

main()
{
	int i;

	for (i = 0; i < 256; i++) {
		if (i == 0)
			printf("%d = %c ", i, (char)i);
		else if (i % 10 == 0)
			printf("\n");
		else
			printf("%d = %c ", i, (char)i);
	}
}
