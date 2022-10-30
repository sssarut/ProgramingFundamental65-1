#include <Wire.h>
#include <string.h>
# define DEVICE 1
char format[100] = "TOKEN#0#";
char format2[100] = "TOKEN#1#";
char *tmpmessage;
char message[100];
char *buffer;
char strget = '0';
char c;
int i;
int target;

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
	tmpmessage = (char *)malloc(sizeof(char) * 100);
	buffer = (char *)malloc(sizeof(char) * 100);
  gone(buffer);
	strcpy(buffer, format);
	strcpy(tmpmessage, "");
	tmpmessage[0] = '\0';
}

//---------------------------------------------------------//

void loop(void)
{
	delay(500);
	tmpmessage = serial_to_buffer(tmpmessage);
  //Serial.println(buffer);
	if(tmpmessage[0] != '\0' && buffer[6] == '0')
	{
		strcpy(buffer, format2);
    //Serial.println("Format buffer");
    //Serial.println(buffer);
		strncat(buffer, tmpmessage, 1);
    //Serial.println(buffer);
		//target = tmpmessage[0] - '0';
		strcat(buffer, "#");
    //Serial.println(buffer);
    //Serial.println("Message Stored");
    //Serial.println(tmpmessage);
    tmpmessage++;
    //Serial.println(tmpmessage);
		strcat(buffer, tmpmessage);
    //Serial.println(buffer);
		wire_send(2, buffer, 0);
    //Serial.println(buffer);
		strcpy(buffer, format);
		strcpy(tmpmessage, "");
	}
	else
	{
		wire_send(2, buffer, 0);
	}
	delay(500);
	Wire.requestFrom(2, 90);
	buffer = wire_to_buffer(buffer);
	wire_send(3, buffer, 0);
	strcpy(buffer, format);
	delay(500);
	Wire.requestFrom(3, 90);
	buffer = wire_to_buffer(buffer);
  //Serial.println(buffer);
	if(buffer[6] == '1')
	{
		if(buffer[8] == '1')
		{
			buffer_to_serial(buffer, 10);
      gone(buffer);
			strcpy(buffer, format);
		}
	}
	//Serial.println(buffer);
}


//---------------------------------------------------------//

char *wire_to_buffer(char *str)
{
	i = 0;
	while(Wire.available())
	{
		c = Wire.read();
    if(c != '\n' && c != '\0')
    {
      if(c == '\r')
        continue;
      if(c >= 32 && c <= '~')
        str[i] = c;
      i++;
      continue;
    }
    else
      str[i] = '\0';
	}
  str[i] = '\0';
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
	Wire.beginTransmission(send);
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


//---------------------------------------------------------//

char *cut(char *str)
{
	char *tab;

	i = 1;
	int j = 0;
	while(str[i] != 's')
	{
		tab[j] = str[i];
		j++;
		i++;
	}
  //Serial.println("TAB");
  //Serial.println(tab);
	return (tab);
}


void gone(char *str)
{
   i = 0;
   while(i < 90)
   {
    str[i] = '\0';
    i++;
   }
}
