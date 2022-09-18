#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char	str1[1000];
	char	pain[5] = "aeiou";
	char	c;
	int		n = 0;
	int		i = 0;
	int		flag = 0;

	printf("Insert your encoded text : ");
	scanf("%s", str1);
	while ((str1[n] >= 'a' && str1[n] <= 'z') || str1[n] == ' ')
	{
		flag = 0;
		i = 0;
		while (i < 5)
		{
			if(str1[n] != ' ' && str1[n + 1] != ' ' && str1[n + 2] != ' ')
			{
				if(str1[n] == pain[i] && str1[n + 1] == 'p' && str1[n + 2] == pain[i])
				{
					c = str1[n];
					write(1, &c, 1);
					n = n + 2;
					i = 6;
					flag = 1;
				}
			}
			i++;
		}
		if(flag != 1)
		{
			c = str1[n];
			write(1, &c, 1);
		}
		n++;
	}
	return (0);
}
