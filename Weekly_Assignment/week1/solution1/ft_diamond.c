#include <stdio.h>
#include <stdlib.h>

int	*fill(int *arr, int nbr, int offset)
{
	int	n;

	n = 0;
	while (n <= offset)
	{
		arr[nbr - (1 + n)] = 1;
		arr[nbr - (1 - n)] = 1;
		n++;
	}
	return (arr);
}

int	main(void)
{
	int	nbr;
	int	**arr;
	int	idx;
	int	idx2;
	int	len;
	int	offset;
	int	flag;
	int	i;

	i = 0;
	printf("Enter a number : ");
	scanf("%d", &nbr);
	len = (2 * nbr) - 1;
	arr = (int **)malloc(sizeof(int *) * len);
	while (i < len)
	{
		arr[i] = malloc(sizeof(int) * len);
		i++;
	}
	idx = 0;
	offset = 0;
	flag = 0;
	while (idx < len)
	{
		arr[idx] = fill(arr[idx], nbr, offset);
		if (offset == nbr - 1)
			flag = 1;
		if (flag == 0)
			offset++;
		if (flag == 1)
			offset--;
		idx++;
	}
	idx = 0;
	while (idx < len)
	{
		idx2 = 0;
		while (idx2 < len)
		{
			if (arr[idx][idx2] == 1)
				printf("*");
			else
				printf(" ");
			idx2++;
		}
		printf("\n");
		idx++;
	}
	return (0);
}
