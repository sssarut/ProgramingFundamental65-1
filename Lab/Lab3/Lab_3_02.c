#include <stdio.h>

int	main(void)
{
	int	n;
	int	i;
	int	sum;

	n = 1;
	while (n <= 10000)
	{
		i = 1;
		sum = 0;
		while (i < n)
		{
			if(n % i == 0)
				sum += i;
			i++;
		}
		if (sum == n)
			printf("%d\n", n);
		n++;
	}
	return (0);
}
