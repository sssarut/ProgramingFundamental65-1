# define L_W_R
# define L_W_Y
# define L_W_G
# define W_PIN

# define L_S_R
# define L_S_Y
# define L_S_G
# define S_PIN

# define L_WA_R
# define L_WA_G
# define WA_PIN
typedef const struct State 
{
	unsigned long Out;
	unsigned long Delay;
	unsigned long Next[7];
} State;
int	input;
int	input1;
int	input2;
int	input3;
int S = 2;


State FSM[7] = 
{
	//RGRYGRYG
	{B10001100, 2000, {}}, //West Green 0
	{B10100001, 2000, {}}, //South Green 1
	{B01100100, 2000, {2, }}, //Walk Green 2
	{B01010100, 2000, {}}, //Wait for West, Walk on 3
	{B00010100, 2000, {}}, //Wait for West, walk off 4
	{B01100010, 2000, {}}, //Wait for south, walk on 5
	{B00100010, 2000, {}} //Wait for south, walk off 6
	//{B01001100, 2000, {}},
}

void setup(void)
{
	pinMode(L_W_R, OUTPUT);
	pinMode(L_W_G, OUTPUT);
	pinMode(L_W_Y, OUTPUT);
	pinMode(W_PIN, INPUT);

	pinMode(L_S_R, OUTPUT);
	pinMode(L_S_G, OUTPUT);
	pinMode(L_S_Y, OUTPUT);
	pinMode(S_PIN, INPUT);
	
	pinMode(L_WA_R, OUTPUT);
	pinMode(L_WA_G, OUTPUT);
	pinMode(WA_PIN, INPUT);
}

void loop(void)
{
	digitalWrite(L_S_G, FSM[S].Out & B00000001);
	digitalWrite(L_S_Y, FSM[S].Out & B00000010);
	digitalWrite(L_S_R, FSM[S].Out & B00000100);
	digitalWrite(L_S_G, FSM[S].Out & B00001000);
	digitalWrite(L_S_Y, FSM[S].Out & B00010000);
	digitalWrite(L_S_R, FSM[S].Out & B00100000);
	digitalWrite(L_WA_G, FSM[S].Out & B01000000);
	digitalWrite(L_WA_R, FSM[S].Out & B10000000);

	delay(FSM[S].Dela);

	input1 = digitalRead(W_PIN);
	input2 = digitalRead(S_PIN);
	input3 = digitalRead(WA_PIN);

	input = input3 * 4 + input2 * 2 + input1;
	S = FSM[S].Next[input];
}
