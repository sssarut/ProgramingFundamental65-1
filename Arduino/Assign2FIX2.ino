#include<ButtonDebounce.h>

#define R_LED 2 
#define Y_LED 3
#define G_LED 4

#define R_BUTTON 10
#define Y_BUTTON 11
#define G_BUTTON 12

ButtonDebounce R_S(10, 250);
ButtonDebounce Y_S(11, 250);
ButtonDebounce G_S(12, 250);

unsigned long	R_TIMER = 0;
unsigned long	Y_TIMER = 0;
unsigned long	G_TIMER = 0;

int	R_ST = 0;
int	Y_ST = 0;
int	G_ST = 0;

void	setup(void)
{
	pinMode(R_BUTTON, INPUT_PULLUP);
	pinMode(R_LED, OUTPUT);
	pinMode(Y_BUTTON, INPUT_PULLUP);
	pinMode(Y_LED, OUTPUT);
	pinMode(G_BUTTON, INPUT_PULLUP);
	pinMode(G_LED, OUTPUT);
}

void	loop(void)
{
	R_S.update();
	Y_S.update();
	G_S.update();
	//Turn green light on
	if(digitalRead(G_BUTTON) == LOW && G_ST == 0 && millis() - G_TIMER >= 250)
	{
		G_TIMER = millis();
		digitalWrite(G_LED, HIGH);
		G_ST = 1;
	}
	else if(digitalRead(G_BUTTON) == LOW && G_ST == 1 && millis() - G_TIMER >= 250)
	{
		digitalWrite(G_LED, LOW);
		G_ST = 0;
	}
	if(millis() - G_TIMER >= 3000 && G_ST == 1)
	{
		digitalWrite(G_LED, LOW);
		G_ST = 0;
	}
}
