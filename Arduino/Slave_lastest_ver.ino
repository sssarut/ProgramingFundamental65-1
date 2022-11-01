#include <Wire.h>
#include <string.h>
# define DEVICE 2
char format[100] = "TOKEN#0#";
char format2[100] = "TOKEN#1#";
char *tmpmessage;
char *buffer;
char strget = '0';
char c;
int i;
int state = 0;
int target;

void  setup(void)
{
  Wire.begin(DEVICE);
  Wire.onReceive(ReceiveEvent);
  Wire.onRequest(RequestEvent);
  Serial.begin(9600);
  tmpmessage = (char *)malloc(sizeof(char) * 100);
  buffer = (char *)malloc(sizeof(char) * 100);
  gone(buffer);
  strcpy(buffer, format);
  strcpy(tmpmessage, "");
  tmpmessage[0] = '\0';
}

void  loop(void)
{
  delay(500);  
  if(state == 0 && Serial.available())
  {
    tmpmessage = serial_to_buffer(tmpmessage);
    state = 1;
  }
  //Serial.println(buffer);
}

//---------------------------------------------------------//
void  ReceiveEvent(void)
{
  buffer = wire_to_buffer(buffer);
  Serial.println(buffer);
  if(buffer[6] == '0')
  {
    if(state == 1)
    {
      strcpy(buffer, format2);
      strncat(buffer, tmpmessage, 1);
      //target = tmpmessage[0] - '0';
      strcat(buffer, "#");
      tmpmessage++;
      strcat(buffer, tmpmessage);
      strcpy(tmpmessage, "");
      state = 0;
    }
  }
  else if(buffer[6] == '1')
  {
    if(buffer[8] == '0' + DEVICE)
    {
      //Serial.println(buffer);
      buffer_to_serial(buffer, 10);
      buffer = gone(buffer);
      strcpy(buffer, format);
      //Serial.println("buffer");
      //Serial.println(buffer);
    }
  }
}


//---------------------------------------------------------//

void  RequestEvent(void)
{
  
  if(buffer[5] == '#')
  {
    wire_send(0, buffer, 0);
    strcpy(buffer, format);
  }
  else 
    wire_send(0, format, 0);
}


//---------------------------------------------------------//
//---------------------------------------------------------//
//---------------------------------------------------------//
//---------------------------------------------------------//
//---------------------------------------------------------//
//---------------------------------------------------------//
//---------------------------------------------------------//
//---------------------------------------------------------//

char *wire_to_buffer(char *str)
{
  str = gone(str);
  i = 0;
  while(Wire.available())
  {
    c = Wire.read();
    if(c != '\n'&& c != '\0')
    {
      if(c == '\r')
        continue;
      if(c>=32 && c<='~')
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
  while(str[i])
  {
    Wire.write(str[i]);
    i++;
  }
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

char *cut(char *str, int start)
{
  char *tab;

  i = start;
  int j = 0;
  while(str[i])
  {
    tab[j] = str[i];
    j++;
    i++;
  }
  return (tab);
}

char *gone(char *str)
{
  i = 0;
  while(i<90){
    str[i]='\0';
    i++;
  }
  return (str);
}
