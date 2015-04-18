#include <stdio.h>

main()
{
	int i;

	printf("The numbers from 0 to 100:\n");
	for (i = 0; i <= 100; i++)
		if (i == 0)
			printf(" %d", i);
		else if (i % 10 == 0)
			printf(" %d\n", i);
		else printf(" %d", i);
	printf("\n");

	printf("All numbers we represent using the 10 numbers:\n");
	for (i = 0; i < 10; i++)
		printf(" %d", i);
	printf("\n\n");

	printf("Two digit number = 10*a+b or ab.\n");
	printf("97=10*9+7\n");
	printf("45=10*4+5\n");
	printf("23=10*2+3\n");
	printf("\n");
}
