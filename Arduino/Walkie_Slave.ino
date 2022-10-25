#include <Wire.h>
# define DEVICE 2

String	buffer = "";
char	c;

void	setup(void)
{
	Wire.begin(DEVICE);
	Serial.begin(9600);
	Wire.onRequest(event);
	Wire.onReceive(event2);
}

void	loop(void)
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
		}
	}
}

void	event(void)
{
	if(buffer != "")
	{
		int t = 0;
		while(buffer[t])
		{
			c = buffer[t];
			Wire.write(c);
			t++;
		}
	}
	else if(buffer == "")
		Wire.write("#");
	else
		Wire.write("1Error");
	buffer = "";
}

void	event2(void)
{
	while(Wire.available())
	{
		c = Wire.read();
		if(c >= 32 && c <= 126)
			Serial.print(c);
	}
}
