#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int **put(int x, int y, int **tab, int n, int m)
{
	tab[x][y] = 9;
	if(x > 0)
	{
		if (y > 0)
		{
			if (tab[x - 1][y - 1] != 9)
				tab[x - 1][y - 1] += 1;
		}
		if (tab[x - 1][y - 0] != 9)
			tab[x - 1][y - 0] += 1;
		if (y < n - 1)
		{
			if (tab[x - 1][y + 1] != 9)
				tab[x - 1][y + 1] += 1;
		}
	}
	if (y > 0)
	{
		if (tab[x - 0][y - 1] != 9)
			tab[x - 0][y - 1] += 1;
	}
	if (y < n - 1)
	{
		if (tab[x - 0][y + 1] != 9)
			tab[x - 0][y + 1] += 1;
	}
	if (x < m - 1)
	{
		if (y > 0)
		{
			if (tab[x + 1][y - 1] != 9)
				tab[x + 1][y - 1] += 1;
		}
		if (tab[x + 1][y - 0] != 9)
			tab[x + 1][y - 0] += 1;
		if (y < n - 1)
		{
			if (tab[x + 1][y + 1] != 9)
				tab[x + 1][y + 1] += 1;
		}
	}
	return (tab);
}
	
int main(void)
{
	int	m;
	int	n;
	int **tab;
	int i;
	int p;
	int x;
	int y;

	printf("Input your width : ");
	scanf("%d", &m);
	printf("Input your height : ");
	scanf("%d", &n);
	tab = (int **)malloc(sizeof(int *) * n);
	i = 0;
	while (i < n)
	{
		tab[i] = (int *)malloc(sizeof(int) * m);
		i++;
	}
	i = 0;
	while (i < n)
	{
		p = 0;
		while (p < m)
		{
			tab[i][p] = 0;
			p++;
		}
		i++;
	}
	printf("How many bomb do you want? : ");
	scanf("%d", &i);
	p = 0;
	while (p < i)
	{
		printf("Input your bomb cordinate in x y format : ");
		scanf("%d %d", &x, &y);
		//tab = put(x, y, tab, n, m);
		p++;
	}
	i = 0;
	while (i < n)
	{
		p = 0;
		while (p < m)
		{
			if (tab[n][m] == 9)
				printf("*");
			else 
				printf("%d", tab[n][m]);
			p++;
		}
		printf("\n");
		i++;
	}
	return (0);
}
