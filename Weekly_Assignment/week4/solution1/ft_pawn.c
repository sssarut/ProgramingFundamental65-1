#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	**mark(int **tab, int x, int y)
{
	int	i = 0;
	int	tx;
	int	ty;

//	printf("Enter mark func");
	while (i < 8)
	{
		tab[i][y] = 1;
		tab[x][i] = 1;
		i++;
	}
	tx = x;
	ty = y;
	i = 0;
	while (i <= 7)
	{
		if(tx + i <= 7 && ty + i <= 7)
			tab[tx + i][ty + i] = 1;
		if(tx - i >= 0 && ty - i >= 0)
			tab[tx - i][ty - i] = 1;
		if(tx + i <= 7 && ty - i >= 0)
			tab[tx + i][ty - i] = 1;
		if(tx - i >= 0 && ty + i <= 7)
			tab[tx - i][ty + i] = 1;
		i++;
	}
	return (tab);
}

int	main(void)
{
	int	**tab;
	int	n;
//	int	*posit;
	int	count = 0;
	int	i = 0;
	int	x;
	int y;

	tab = (int **)malloc(sizeof(int	*) * 8);
	while (i < 8)
	{
		tab[i] = (int *)malloc(sizeof(int) * 8);
		if (tab[i] == NULL)
			printf("Error malloc sub array");
		i++;
	}
	if (tab == NULL)
		printf("Error malloc main folder");
	i = 0;
	printf("How many queen do you want? : ");
	scanf("%d", &n);
//	posit = (int *)malloc(sizeof(int) * n * 2);
	while (i < n)
	{
		printf("Please insert the %d queen position x y : ", (i + 1));
		scanf("%d %d", &x, &y);
		if(x > 8 || x < 1 || y > 8 || x < 1)
		{
			printf("Please insert in (x, y) format and value should be between 1 - 8");
			return (0);
		}
//		posit[(2 * i)] = x - 1;
//		posit[(2 * i) + 1] = y - 1;
//		printf("checkpoint");
		tab = mark(tab, x - 1, y - 1);
		i++;
	}
	x = 0;
	while (x <= 7)
	{
		y = 0;
		while (y <= 7)
		{
			if(tab[x][y] != 1)
				count++;
			y++;
		}
		x++;
	}
	printf("Number of slot you can place pawn safely : %d", count);
	return (0);
}
