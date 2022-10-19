#include <Wire.h>
#include <string.h>
# define Device 5

String buffer = "";
int switch = 1;
String format = "TOKEN#"

void	setup(void)
{
	// Initial the Serial process & Begin itself as Slave
	Serial.begin(9600);
	switch();	
}

void	loop(void)
{
	// Get the first input normally its is target device number
	// Switch itself as master
	if (Serial.available() && switch == 0)
	{
		char n = Serial.read();
		switch();
	}
	// Get the message input stor it in buffer
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
	// Format the message as token and send it to device next in the line 
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
	// Switch form master mode to slave mode and vice versa the switch vaiable mean the state 0 is  slave 1 is master
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
	// Run on the receiving of token
	//012345678
	//TOKEN#0#
	//TOKEN#1#T#message
	While (1 < Wire.available())
	{
		char a = Wire.read();
		buffer += a;
	}
	buffer += '\0';
	// Stored Token in the buffer & if its is on state 1 or 0
	// If state is 0
	if (buffer[6] == '0')
	{
		// Pass token to next-in-line device
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
		buffer = "";
	}
	// If State is 1
	else if (buffer[6] == '1')
	{
		// and the target is this device
		if (buffer[8] - '0' = Device - 1)
		{
			// Print out the message
			int p = 10;
			while (buffer[p])
			{
				Serial.print(buffer[p]);
				p++;
			}
			Serial.println('\n');
			// Reset token to 0 state
			buffer = "TOKEN#0#";
		}
		// If target is this device buffer should be state 0 and if its not it will pass by the occupied token to
		// the next-in-line device
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
