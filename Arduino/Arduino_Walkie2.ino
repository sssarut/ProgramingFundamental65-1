#include <Wire.h>
# define Own_Device 1
# define Next 2

String buffer;
int state;

void setup(void)
{
	Serial.begin(9600);
	state = 1;
	mode();
}

void loop(void)
{
	while (Serial.available())
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
				if(state != 1)
					mode();
				buffer = "";
				continue;
			}
			if(state == 1)
			{
				Wire.beginTransmission(Next);
				int i = 0;
				while (buffer[i])
				{
					Wire.write(buffer[i]);
					i += 1;
				}
				Wire.endTransmission();
			}
			else 
				Serial.println("Wrong mode");
			buffer = "";

		}
	}
}

void mode(void)
{
	if(state == 0)
	{
		master();
		state = 1;
		Serial.println("In the master mode");
	}
	else if(state == 1)
	{
		slave();
		state = 0;
		Serial.println("In the slave mode");
	}
}

void event(int howMany)
{
	while (1 < Wire.available())
	{
		char a = Wire.read();
		Serial.print(c);
	}
	char a = Wire.read();
	Serial.println(c);
}

void master(void)
{
	Wire.begin();
	Serial.println("Master mode");
}

void slave(void)
{
	Wire.begin(Own_Device);
	Wire.onReceive(event);
	Serial.println("Master mode");
}
