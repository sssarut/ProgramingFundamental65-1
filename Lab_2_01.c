#include <stdio.h>

int	main(void)
{
	int	nbr;
	int	i;

	i = 2;
	printf("Enter number : ");
	scanf("%d", &nbr);
	printf("Factory result : ");
	while (i <= nbr)
	{
		if (nbr == i)
		{
			printf("%d\n", nbr);
			return (0);
		}
		else if (nbr % i == 0)
		{
			printf("%d x ", i);
			nbr /= i;
		}
		else
		{
			i++;
		}
	}
	printf("%d\n", nbr);
	return (0);
}
