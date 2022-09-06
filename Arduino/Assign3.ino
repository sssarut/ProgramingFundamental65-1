# define A_SWITCH 10
# define B_SWITCH 11

const int	bitSet[12] = {B11000000, B11111001, B10100100, B10110000, B10011001, B10010010, B10000010, B11111000, B10000000, B10010000, B11000111, B11000010};
const int	SegPin[8] = {2, 3, 4, 5, 6, 7, 8, 9};

int	start = 0;
int	nbr = 0;
int	WIN = 0;
int	guess = 0;
int point;

void	setup(void)
{
	int	i = 0;
	randomSeed(analogRead(A0));
	pinMode(A_SWITCH, INPUT_PULLUP);
	pinMode(B_SWITCH, INPUT_PULLUP);
	while (i < 8)
	{
		pinMode(SegPin[i], OUTPUT
	}
}

void	loop(void)
{
	if(WIN == 1 || start == 0)
	{
		nbr = random(1, 10);
		WIN = 0;
	}
	if(digitalRead(A_SWITCH) == LOW)
	{
		guess++;
		start = 1;
	}
	if(guess == 10)
		guess = 1;
	display(guess);
	if(digitalRead(B_SWITCH) == LOW)
	{
		point = nbr - guess;
		if(point > 0)
			display(11);
		else if(point < 0)
			display(10);
		else
		{
			display(0);
			WIN = 1;
		}
	}
}

void	display(int	num)
{
	bool isBitSet;

	for (int segment = 0; segment < 8; segment++)
	{
		isBitSet = bitRead(bitSet[num], segment);
		digitalWrite(SegPin[segment], isBitSet);
	}
}
