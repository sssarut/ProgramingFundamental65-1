#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char	*str1;
	char	str2[1000];
	char	pain[5] = "aeiou";
	int		n = 0;
	int		i = 0;
	int		j = 0;
	int		flag = 0;

	printf("Insert your encoded text : ");
	str1 = (char *)malloc(sizeof(char) * 1000);
	scanf("%s", str1);
	while (n < 1000)
	{
		flag = 0;
		i = 0;
		while (i < 5)
		{
			if(str1[n] == pain[i] && str1[n + 1] == 'p' && str1[n + 2] == pain[i])
			{
				str2[j] = str1[n];
				j++;
				n = n + 2;
				i = 6;
				flag = 1;
			}
			i++;
		}
		if(flag != 1)
		{
			str2[j] = str1[n];
			j++;
		}
		n++;
	}
	printf("%s", str2);
	return (0);
}
