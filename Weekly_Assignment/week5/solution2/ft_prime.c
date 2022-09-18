#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int	nbr;
	int	run;
	while (1)
	{
		printf("Insert number : ");
		scanf("%d", &nbr);
		if(nbr == -99)
			return (0);
		else if(nbr <= 1)
			printf("This number is not a prime number\n");
		else
		{
			run = 2;
			while (run < nbr / 2)
			{
				if(nbr % run == 0)
				{
					printf("This number is not a prime number\n");
					run = nbr;
				}
				run++;
			}
			if(run != nbr + 1)
			{
				printf("This number is a prime number\n");
			}
		}
	}
	return (0);
}
