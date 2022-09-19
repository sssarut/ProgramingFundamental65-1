#include <stdio.h>
#include <unistd.h>

void swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int main(void)
{
	int a;
	int b;
	printf("Insert A ,B : ");
	scanf("%d %d", &a, &b);
	swap(&a, &b);
	printf("A = %d, B = %d", a, b);
	return (0);
}
