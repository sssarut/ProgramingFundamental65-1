#define R_LED 2 
#define Y_LED 3
#define G_LED 4

#define R_BUTTON 10
#define Y_BUTTON 11
#define G_BUTTON 12

unsigned long	R_TIMER = 0;
unsigned long	Y_TIMER = 0;
unsigned long	G_TIMER = 0;



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
	if(digitalRead(G_BUTTON) == LOW)
	{
		G_TIMER = millis();
		digitalWrite(G_LED, HIGH);
	}
	if(millis() - G_TIMER >= 250)
	{
		G_TIMER = 0;
		digitalWrite(G_LED, LOW);
	}
}
