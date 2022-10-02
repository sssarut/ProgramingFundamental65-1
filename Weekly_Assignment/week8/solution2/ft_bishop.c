#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	*posit;
	int	x = 0;
	int	y = 0;
	int	num;
	int	i = 0;
	int	count = 0;
	int	subcount = 0;

	printf("How many rook do you want? : ");
	scanf("%d", &num);
	posit = (int *)malloc(sizeof(int) * 2 * num);
	if(posit == NULL)
	{
		printf("Error : Can't allocate the memory");
		return(0);
	}
	while (i < num)
	{
		printf("Please insert the %d position in x y format : ", i + 1);
		scanf("%d %d", &x, &y);
		if(x < 1 || y < 1 || x > 8 || y > 8)
		{
			printf("Your argument doesn't seem to be in x y format or you input the value that aren't between 1 and 8");
			return (0);
		}
		posit[(i * 2)] = x - 1;
		posit[(i * 2) + 1] = y - 1;
		i++;
	}
	x = 0;
	i = 0;
	while (x < 8)
	{
		y = 0;
		while (y < 8)
		{
			subcount = 0;
			i = 0;
			while (i < num)
			{
				/*if(x == posit[(2 * i)] || y == posit[(2 * i) + 1])
					y = y;*/
				//else 
				if((x - posit[(2 * i)]) - (y - posit[(2 * i) + 1]) == 0 || (x - posit[(2 * i)]) + (y - posit[(2 * i) + 1]) == 0)
					x = x;
				else
					subcount++;
				i++;
			}
			if(subcount == num)
				count++;
			y++;
		}
		x++;
	}
	printf("The number of slot you can play your pawn safely is : %d", count);
	return (0);
}
