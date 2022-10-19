#include <Wire.h>
#include <string.h>
# define Device 5

String buffer = "";
int switch = 1;
String format = "TOKEN#"

void	setup(void)
{
	Serial.begin(9600);
	switch();	
}

void	loop(void)
{
	if (Serial.available() && switch == 0)
	{
		char n = Serial.read();
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
		strcat(format, "1#");
		strcat(format, n);
		strcat(format, "#");
		strcat(format, buffer);
		Wire.beginTransmission(Device);
		int i = 0;
		while (format[i])
		{
			Wire.write(format[i]);
			i++;
		}
		Wire.endTransmission();
		switch();
		format = "TOKEN#";
		buffer = "";
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
		Wire.begin(Device - 1);
		Wire.onReceive(receiveEvent);
	}
	switch = !switch;
}

void	receiveEvent(void)
{
	//012345678
	//TOKEN#0#
	//TOKEN#1#T#message
	While (1 < Wire.available())
	{
		char a = Wire.read();
		buffer += a;
	}
	buffer += '\0';
	if (buffer[6] == '0')
	{
		switch();
		Wire.beginTransmission(Device);
		int j = 0;
		while (buffer[j])
		{
			Wire.write(buffer[j]);
			j++;
		}
		Wire.endTransmission();
		switch();
	}
	else if (buffer[6] == '1')
	{
		if (buffer[8] - '0' = Device - 1)
		{
			int p = 10;
			while (buffer[p])
			{
				Serial.print(buffer[p]);
				p++;
			}
			Serial.println('\n');
			buffer = "TOKEN#0#";
		}
		switch();
		Wire.beginTransmission(Device);
		int l = 0;
		while (buffer[l])
		{
			Wire.write(buffer[l]);
			l++;
		}
		Wire.endTransmission();
		switch();
	}
}
