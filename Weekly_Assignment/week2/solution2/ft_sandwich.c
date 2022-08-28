#include <stdio.h>

int	ft_is_odd(int nb)
{
	if (nb % 2 == 1)
		return (1);
	else 
		return (0);
}

int	main(void)
{
	int	n;
	int nb[10];
	int	tab[10];

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
		tab[n] = ft_is_odd(nb[n]);
		n++;
	}
	printf("\n");
	printf("Result : ");
	n = 0;
	while (n < 10)
	{
		if (n != 0 && n != 9)
		{
			if (tab[n - 1] + tab[n + 1] == 2)
				printf("%d ", nb[n]);
		}
		n++;
	}
	return (0);
}
