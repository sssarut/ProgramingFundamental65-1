#include <stdio.h>

int	ft_odd_or_even(int nb)
{
	if (nb % 2 == 1)
		return (0);
	else 
		return (1);
}

int	main(void)
{
	int	n;
	int nb[10];

	n = 0;
	while (n < 10)
	{
		printf("Please insert the %d index of the array : ", n);
		scanf("%d", &nb[n]);
		n++;
	}
	n = 0;	
	printf("Data in array : ");
	while (n < 10)
	{
		printf("%d ", nb[n]);
		n++;
	}
	printf("\n");
	n = 0;
	printf("Result : ");
	while (n < 10)
	{
		if(n != 0 && n != 9)
		{
			if(ft_odd_or_even(nb[n - 1]) == 0 && ft_odd_or_even(nb[n + 1]) == 0)
				printf("%d ", nb[n]);
		}
		n++;
	}
	return (0);
}
