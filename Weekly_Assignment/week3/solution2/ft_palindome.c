#include <stdio.h>
#include <string.h>
#include <stdlib.h>
size_t MAX = 1000;

char	*ft_translate(char *str, int len)
{
	char	*tab = malloc(MAX);
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (n < len)
	{
		if(str[n] >= 'a' && str[n] <= 'z')
		{
			tab[i] = str[n];
			i++;
			n++;
		}
		else if(str[n] >= 'A' && str[n] <= 'Z')
		{
			tab[i] = str[n] + 32;
			i++;
			n++;
		}
		else 
		{
			n++;
		}
	}
	return (tab);
}
int		main(void)
{
	char	*str = malloc(MAX);
	char	*str2 = malloc(MAX);
	char	*str3 = malloc(MAX);
	int		len;
	int		a;
	int		flag;

	printf("Input a string : ");
	getline(&str, &MAX, stdin);
	len = strlen(str);
	str2 = ft_translate(str, len);
	len = strlen(str2);
	a = 0;
	flag = 0;
	while (a < len)
	{
		str3[(len - 1) - a] = str2[a];
		a++;
	}
	a = 0;
	while (a < len)
	{
		if(str2[a] != str3[a])
			flag = 1;
		a++;
	}
	if(flag == 1)
		printf("String : %s is not a palindome", str);
	else
		printf("String : %s is a palindome", str);
	return (0);
}
