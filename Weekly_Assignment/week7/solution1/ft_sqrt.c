#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	double num;
	double value;

	printf("Insert : ");
	scanf("%lf", &num);
	value = sqrt(num);
	printf("NUM : %.2lf", value);
}
