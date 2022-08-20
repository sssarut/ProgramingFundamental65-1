#include <stdio.h>

int	main(void)
{
	int	x;
	int	y;
	int	temp;

	printf("Enter first number : ");
	scanf("%d", &x);
	printf("Enter second number : ");
	scanf("%d", &y);
	if (x > y)
	{
		temp = x;
		x = y;
		y = temp;
	}
	temp = y;
	while (temp >= 0)
	{
		if (x % temp == 0 && y % temp == 0)
		{
			printf("Greatest common divisor = %d\n", temp);
			return (0);
		}
		temp--;
	}
	return (0);
}
