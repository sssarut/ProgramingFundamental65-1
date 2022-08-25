#include <stdio.h>

int	main(void)
{
	int	nbr;
	int	sum;
	int	temp;

	printf("Enter your number : ");
	scanf("%d", &nbr);
	while (nbr >= 10)
	{
		temp = nbr;
		sum = 0;
		while (temp > 0)
		{
			sum += (temp % 10);
			temp /= 10;
		}
		nbr = sum;
	}
	printf("Answer is %d", nbr);
	return (0);
}
