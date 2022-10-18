#include <Wire.h>
#include <string.h>
int		SUB_ADD[2] = {2, 3};
char	message[50] = "";
int		target = 0;
String	buffer;

void	setup(void)
{
	Wire.begin();
	Serial.begin(9600);
}

void	loop(void)
{
	int		i = 0;
	char	c;
	int		flag = 0;

	delay(50);
	while(Serial.available())
	{
		char a = Serial.read();
		if (c != '\n')
		{
			if (c == '\r')
				continue;
			buffer += c;
			continue;
		}
		else 
		{
			buffer += '\0';
		}
	}
	while(i < 2)
	{
		Wire.requestFrom(SUB_ADD[i], 32)
		if (Wire.available() > 0)
		{
			while (1 < Wire.available())
			{
				c = Wire.read();
				strcat(message, c);
			}
			char *ptr = strtok(message, "#");
			while (ptr != NULL)
			{
				if (flag == 2)
				{
					strcpy(message, ptr);
					flag = 0;
				}
				if (flag == 1)
				{
					flag += 1;
					target = ptr - '0';
				}
				if (ptr == "0" && flag <= 0)
					break;
				else if (ptr == "1")
					flag = 1;
				ptr = strtok(NULL, "#");
			}
		}
		if (target == 1)
		{
			Serial.println(message);
			target = 0;
		}
		else if (target > 0)
		{
			Wire.beginTransmission(target);
			Wire.write(message);
			Wire.endTransmission();
			target = 0;
		}
		i++;
	}
}


