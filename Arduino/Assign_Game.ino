#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

# define CONTROL 1
# define RESET 4
# define SCREEN_W 128
# define SCREEN_H 32
# define OLED_RESET 4

const int	PAD_SPEED = 45;
const int	BALL_SPEED = 1;
const uint8_t PAD_HEIGHT = 12;
const uint8_t ATR_HEIGHT = 4;
int score = 0;
bool BALL_RESET = false;
uint8_t BALL_X = 64;
uint8_t BALL_Y = 16;
uint8_t BALL_DIR_X = -1;
uint8_t BALL_DIR_Y = -1;
unsigned long BALL_TIMER;
unsigned long PADD_TIMER;
unsigned long MAIN_TIMER;
const uint8_t PLAYER_X = 105;
uint8_t PLAYER_Y = 6;
bool UPDATE = false;
bool ATARI = false;
bool GAME_ST = false;
bool ATR_FLAG = false;
Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, OLED_RESET);

void drawAtari(void)
{
	//115 119 123
	//5 13 21 29
	int j;
	int k;

	j = 115;
	while (j <= 123)
	{
		k = 5
		while (k <= 29)
		{
			display.drawFastVLine (j, k, ATR_HEIGHT, WHITE);
			display.drawFastVLine (j + 1, k, ATR_HEIGHT, WHITE);
			k += 8;
		}
		j += 4;
	}
	//display.drawFastVLine (PLAYER_X, PLAYER_Y, ATR_HEIGHT, WHITE);
}

void drawScreen(void)
{
	display.drawRect(0, 0, 127, 31, WHITE);
}

void drawScore(void)
{
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(63, 0);
	display.println(score);
}

void setup(void)
{
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.display();
	unsigned long start = millis();
	pinMode(BEEPER, OUTPUT);
	pinMode(RESET, INPUT);
	digitalWrite(RESET, HIGH);
	display.clearDisplay();
	drawScreen();
	drawScore();
	while(millis() - start < 2000)
	{
		start = start;
	}
	display.display();
	BALL_TIMER = millis();
	PADD_TIMER = BALL_TIMER;
}

void loop(void)
{
	MAIN_TIMER = millis();
	UPDATE = false;

	drawScreen();
	if (GAME_ST == false)
	{
		BALL_X = random(59, 68);
		BALL_Y = random(12, 19);
		do
		{
			//BALL_DIR_X = random(-1, 2);
			BALL_DIR_Y = random(-1, 2); 
		}
		while (BALL_DIR_Y == 0);
		GAME_ST = true;
	}
	if (MAIN_TIMER > BALL_TIMER)
	{
		uint8_t NEX = BALL_X + BALL_DIR_X;
		uint8_t NEY = BALL_Y + BALL_DIR_Y;
		if(NEX == 0)
		{
			gameOver();
			GAME_ST = false;
		}
		if(NEX == 127)
		{
			BALL_DIR_X = -BALL_DIR_X;
			NEX += BALL_DIR_X;
		}
		if(NEY == 0 || NEY == 31)
		{
			BALL_DIR_Y = -BALL_DIR_Y;
			NEY += BALL_DIR_Y;
		}
		if(NEX == PLAYER_X && NEY >= PLAYER_Y && NEY <= PLAYER_Y + PAD_HEIGHT)
		{
			BALL_DIR_X = -BALL_DIR_X;
			NEX += BALL_DIR_X;
		}
		/*display.drawPixel(BALL_X, BALL_Y, BLACK);
		display.drawPixel(NEX, NEY, WHITE);
		BALL_X = NEX;
		BALL_Y = NEY;
		BALL_TIMER += BALL_SPEED;*/
		UPDATE = true;
	}
	if (MAIN_TIMER > PADD_TIMER)
	{
		PADD_TIMER += PAD_SPEED;
		display.drawFastVLine (PLAYER_X, PLAYER_Y, PAD_HEIGHT, BLACK);
		if (analogRead(CONTROL < 480)
			PLAYER_Y -= 1;
		if (analogRead(CONTROL > 520)
			PLAYER_Y += 1;
		if (PLAYER_Y < 1)
			PLAYER_Y = 1;
		if (PLAYER_Y + PAD_HEIGHT > 31)
			PLAYER_Y = 31 - PAD_HEIGHT;
		display.drawFastVLine (PLAYER_X, PLAYER_Y, PAD_HEIGHT, WHITE);
		UPDATE = true;
	}
	if (NEX >= 115 && NEX <= 123 && NEY >= 5 && NEY <= 29 && display.getPixel(NEX, NEY) == true)
	{
		uint8_t TEMP_Y = NEY;

		score += 1;
		while (display.getPixel(NEX, TEMP_Y - 1) == true)
		{
			TEMP_Y -= 1;
		}
		display.drawFastVLine (NEX, TEMP_Y, ATR_HEIGHT, BLACK);
		display.drawFastVLine (NEX + 1, TEMP_Y, ATR_HEIGHT, BLACK);
		display.drawFastVLine (NEX - 1, TEMP_Y, ATR_HEIGHT, BLACK);
	}
	if (UPDATE)
	{
		display.drawPixel(BALL_X, BALL_Y, BLACK);
		display.drawPixel(NEX, NEY, WHITE);
		BALL_X = NEX;
		BALL_Y = NEY;
		BALL_TIMER += BALL_SPEED;
		drawScore();
		display.display();
	}
}
