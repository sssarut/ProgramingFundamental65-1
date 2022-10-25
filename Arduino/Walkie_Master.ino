#include<Wire.h>
# define DEVICE 1 
String buffer;
int target = 2;
int send;
char c;

void	setup(void)
{
	Wire.begin();
	Serial.begin(9600);
}

void	loop(void)
{
	delay(1000);
	sending();
	Wire.requestFrom(target, 90);
	int i = 0;
	while(Wire.available())
	{
		c = Wire.read();
		if(c >= 32 && c <= 126)
			buffer[i] = c;
		//Serial.print(c);
		i++;
	}
	if(buffer[0] != '#')
	{
		if(buffer[0] - '0' == DEVICE)
		{
			i = 1;
			while(buffer[i])
			{
				c = buffer[i];
				Serial.print(c);
				i++;
			}
		}
		else
		{
			send = buffer[0] = '0';
			i = 1;
			Wire.beginTransmission(send);
			while(buffer[i])
			{
				Wire.write(buffer[i]);
				i++;
			}
			Wire.endTransmission();
		}
	}
	else
		Serial.println("ERROR");
	buffer = "";
	if(target == 2)
		target = 3;
	else
		target = 2;
}

void	sending(void)
{
	while(Serial.available())
	{
		char c = Serial.read();
		if(c != '\n')
		{
			if(c == '\r')
				continue;
			buffer += c;
			continue;
		}
		else
		{
			buffer += '\0';
			if(buffer[0] >= '1' && buffer[0] <= '3')
			{
				send = buffer[0] - '0';
			}
			i = 1;
			Wire.beginTransmission(2);
			while(buffer[i])
			{
				Wire.write(buffer[i]);
				i++;
			}
			Wire.endTransmission();
		}
	}
	buffer = "";
}
