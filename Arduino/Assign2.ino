const int	rightButton = 10;
const int	green = 2;
const int	middleButton = 11;
const int	yellow = 3;
const int	leftButton = 12;
const int	red = 4;

bool	buttonstateGreen = false;
bool	buttonstateYellow = false;
bool	buttonstateRed = false;

bool	stateGreen = false;
bool	stateYellow = false;
bool	stateRed = false;

int	timerGreen = 0;
int	timerYellow = 0;
int	timerRed = 0;

void	checkRight()
{
	if(digitalRead(rightButton) == LOW && stateGreen == false && stateRed != true)
	{
		timerGreen = 3000;
	}
	if(digitalRead(rightButton) == LOW && stateGreen == true)
	{
		timerGreen = 0;
	}
}

void	checkLeft()
{
	if(digitalRead(leftButton) == HIGH && stateRed == false)
	{
		timerRed = 3000;
	}
	if(digitalRead(leftButton) == HIGH && stateRed == true)
	{
		timerRed = 0;
	}
}

void	checkMiddle()
{
	if(digitalRead(middleButton) == LOW && stateYellow == false && stateGreen == false && stateRed == false)
	{
		timerYellow = 2000;
	}
}

void	setup()
{
	pinMode(green, OUTPUT);
	pinMode(rightButton, INPUT_PULLUP);
	pinMode(yellow, OUTPUT);
	pinMode(middleButton, INPUT_PULLUP);
	pinMode(red, OUTPUT);
	pinMode(leftButton, INPUT_PULLUP);

}

void	loop()
{
	delay(100);
	//Check if there are any time added to the timer and turn on the LED
	if(timerGreen != 0 && stateGreen == false)
	{
		stateGreen = true;
		digitalWrite(green, true);
	}
	if(timerYellow != 0 && stateYellow == false)
	{
		stateYellow = true;
		digitalWrite(yellow, true);
	}
	if(timerRed != 0 && stateRed == false)
	{
		stateRed = true;
		digitalWrite(red, true);
	}
	//yellow case
	if(timerYellow != 0 && timerYelllow % 500)
	{
		digitalWrite(yellow, !digitalRead(yellow));
	}
	//Check if there any timer reach 0 and turn it off
	if(timerGreen == 0 && stateGreen == true)
	{
		stateGreen = false;
		digitalWrite(green, false);
	}
	if(timerRed == 0 && stateRed == true)
	{
		stateRed = false;
		digitalWrite(red, false);
	}
	if(timerYellow == 0 && stateYellow == true)
	{
		stateYellow = false
		digitalWrite(yellow, false);
	}
	//Counting down section
	if(timerGreen != 0)
	{
		timerGreen -= 100;
	}
	if(timerYellow != 0)
	{
		timerYellow -= 100;
	}
	if(timerRed != 0)
	{
		timerRed -= 100;
	}
}
