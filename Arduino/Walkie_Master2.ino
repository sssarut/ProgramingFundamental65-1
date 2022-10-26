#include <Wire.h>
#include <string.h>
# define DEVICE 1
char format[100] = "TOKEN#0#"
char format2[100] = "TOKEN#1#"+
986
char tmpmessage[100] = "";
char buffer[100] = "";
char strget = '0';
char c;
int i;
int target = 2;

//0123456789
//TOKEN#0#
//TOKEN#1#T#message


/*
Master(1) =Send=> 2  =Delay= =Request=> 2 =Send=> 3 =Delay= =Request=> 3 
Slave Module Onreceive : Check if have own number if yes reset and serial.print
	if no don't do anything and left it in buffer
	Onrequest : Send everything in buffer 
*/

void setup(void)
{
	Wire.begin();
	Serial.begin(9600);
}

//---------------------------------------------------------//

void loop(void)
{
	delay(500);
	tmpmessage = serial_to_buffer(tmpmessage)
	if(tmpmessage[0] != '\0')
	{
		
	}
}


//---------------------------------------------------------//

char *wire_to_buffer(char *str)
{
	i = 0;
	while(Wire.available())
	{
		c = Wire.read();
		if(c >= '!' && c <= '~')
		{
			str[i] = c;
		}
		i++;
	}
	return (str);
}

//---------------------------------------------------------//

void buffer_to_serial(char *str, int start)
{
	i = start;
	while(str[i])
	{
		c = str[i];
		Serial.print(c);
		i++;
	}
	Serial.println();
}


//---------------------------------------------------------//

void wire_send(int send, char *str, int start)
{
	i = start;
	Wire.begintransmission(send);
	while(str[i])
	{
		Wire.write(str[i]);
		i++;
	}
	Wire.endTransmission();
}


//---------------------------------------------------------//

char *serial_to_buffer(char *str)
{
	i = 0;
	str[0] = '\0';
	while(Serial.available())
	{
		c = Serial.read();
		if(c != '\n')
		{
			if(c == '\r')
				continue;
			str[i] = c;
			i++;
			continue;
		}
		else
			str[i] = '\0';
	}
	return (str);
}
