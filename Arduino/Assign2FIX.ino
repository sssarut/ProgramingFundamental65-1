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
int	timerYellow2 = 0;
int	timerRed = 0;

int	maintimer = 0

void	checkRight()
{
	if(digitalRead(rightButton) == LOW && stateGreen == false && stateRed != true)
	{
		timerGreen = millis();
		timerGreen += 3000;
	}
	if(digitalRead(rightButton) == LOW && stateGreen == true)
	{
		timerGreen = millis();
	}
}

void	checkLeft()
{
	if(digitalRead(leftButton) == HIGH && stateRed == false)
	{
		timerRed = millis();
		timerRed += 3000;
	}
	if(digitalRead(leftButton) == HIGH && stateRed == true)
	{
		timerRed = millis();
		timerRed += 3000;
	}
}

void	checkMiddle()
{
	if(digitalRead(middleButton) == LOW && stateYellow == false && stateGreen == false && stateRed == false)
	{
		timerYellow = millis();
		timerYellow += 2000;
		timerYellow2 = timerYellow - 1500;
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
	//delay(125);
	checkRight();
	checkLeft();
	checkMiddle();
	maintimer = millis();
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
	if(timerYellow != 0 && maintimer == timerYellow2 && timerYellow != timerYellow2)
	{
		digitalWrite(yellow, !digitalRead(yellow));
		timerYellow2 += 500;
	}
	//Check if there any timer reach 0 and turn it off
	if(maintimer == timerGreen && stateGreen == true)
	{
		stateGreen = false;
		digitalWrite(green, false);
		timerGreen = 0;
	}
	if(maintimer == timerRed && stateRed == true)
	{
		stateRed = false;
		digitalWrite(red, false);
		timerRed = 0;
	}
	if(maintimer == timerYellow && stateYellow == true)
	{
		stateYellow = false;
		digitalWrite(yellow, false);
		timerYellow = 0;
	}
	//Counting down section
	i/*if(timerGreen != 0)
	{
		timerGreen -= 125;
	}
	if(timerYellow != 0)
	{
		timerYellow -= 125;
	}
	if(timerRed != 0)
	{
		timerRed -= 125;
	}*/
}
