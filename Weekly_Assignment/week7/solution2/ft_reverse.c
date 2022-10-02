#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void reverse(int len, char *str)
{
	if(len < 0)
		len = len;
	else
	{
		write(1, &str[len], 1);
		reverse(len - 1, str);
	}
}

int main(void)
{
	char	*str;
	int		len;

	printf("Input the string : ");
	str = (char *)malloc(sizeof(char) * 1000);
	scanf("%s", str);
	len = strlen(str) - 1;
	reverse(len, str);
	/*while(len >= 0)
	{
		write(1, &str[len], 1);
		len--;
	}*/
	return (0);
}
