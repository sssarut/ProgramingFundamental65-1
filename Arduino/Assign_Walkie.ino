#include <Wire.h>
#include <string.h>
# define Device 5

String buffer = "";
int switch = 0;

void	setup(void)
{
	Serial.begin(9600);
	switch();	
}

void	loop(void)
{
	if (Serial.available() && switch == 0)
	{
		int n = Serial.read() - '0';
		switch();
	}
	while (Serial.available())
	{
		char c = Serial.read();
		if(c != '\n')
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
	if (switch == 1 && buffer != "")
	{
		Wire.beginTransmission(Device);
		int i = 0;
		while (buffer[i])
		{
			Wire.write(buffer[i]);
			i++;
		}
		Wire.endTransmission();
		switch();

	}
}

void	switch(void)
{
	if (switch == 0)
	{
		Wire.begin();
	}
	else if (switch == 1)
	{
		Wire.begin(Device);
		Wire.onReceive(receiveEvent);
	}
	switch = !switch;
}
