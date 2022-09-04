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
	int		len;
	int		a;
	int		z;

	getline(&str, &MAX, stdin);
	len = strlen(str);
	str2 = ft_translate(str, len);
	len = strlen(str2);
	z = len - 1;
	a = 0;
	while (z >= a)
	{
		if(str2[z] != str2[a])
		{
			printf("%s is not a palindome", str);
			return (0);
		}
		z--;
		a++;
	}
	printf("%s is a palindome", str);
	return (0);
}
