#include<Wire.h>
# define DEVICE 1 
char buffer[100];
int target = 2;
int send;
char c;
int i;

void  setup(void)
{
  Wire.begin();
  Serial.begin(9600);
}

void  loop(void)
{
  delay(1000);
  sending();
  Wire.requestFrom(target, 90);
  int i = 0;
  while(Wire.available())
  {
    c = Wire.read();
    if(c >= '!' && c <= '~')
    {
      //Serial.println("Printable");
      //Serial.println(c);
      buffer[i] = c;
      //Serial.println(buffer[i]);
      //Serial.println(i);
    }
    //else
      //Serial.print(c);
    //Serial.print(buffer[i]);
    i++;
  }
  if(buffer[0] != '#')
  {
    if(buffer[0] == '1')
    {
      i = 1;
      while(buffer[i])
      {
        c = buffer[i];
        Serial.print(c);
        i++;
      }
      Serial.println();
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
  buffer[0] = '\0';
  if(target == 2)
    target = 3;
  else
    target = 2;
}

void  sending(void)
{
  i = 0;
  while(Serial.available())
  {
    char c = Serial.read();
    if(c != '\n')
    {
      if(c == '\r')
        continue;
      buffer[i] = c;
      i++;
      continue;
    }
    else
    {
      buffer[i] = '\0';
      if(buffer[0] >= '1' && buffer[0] <= '3')
      {
        send = buffer[0] - '0';
      }
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
  buffer[0] = '\0';
}
