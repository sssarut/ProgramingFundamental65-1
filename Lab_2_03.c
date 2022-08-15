#include <stdio.h>

int	main(void)
{
	int	x;
	int	y;
	int	i;

	printf("Enter number : ");
	scanf("%d", &i);
	x = 0;
	y = 0;
	while (y != i)
	{	
		if (x == 0 || y == 0 || x == i - 1 || y == i - 1 )
		{
			printf("*");
		}
		else
		{
			printf(" ");
		}
		x++;
		if (y == i)
			return (0);
		if (x == i)
		{
			printf("\n");
			x = 0;
			y++;
		}
	}
	return (0);
}
