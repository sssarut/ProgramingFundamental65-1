#include <Arduino_FreeRTOS.h>
#include "queue.h"

# define RED 8
# define YEL 9
# define GRN 10

# define RED_BTN  2
# define YEL_BTN  3
# define GRN_BTN  4

QueueHandle_t RED_QUE;
QueueHandle_t YEL_QUE;
QueueHandle_t GRN_QUE;
QueueHandle_t SWT_QUE;

void	setup(void)
{
	Serial.begin(9600);
	SWT_QUE = xQueueCreate(10, sizeof(int32_t));
  RED_QUE = xQueueCreate(10, sizeof(int32_t));
  YEL_QUE = xQueueCreate(10, sizeof(int32_t));
  GRN_QUE = xQueueCreate(10, sizeof(int32_t));

	xTaskCreate(vSenderTask, "Sender Task", 100, NULL, 3, NULL);
	xTaskCreate(vReceiverTask, "Receiver Task", 100, NULL, 3, NULL);
	xTaskCreate(RED_CRL, "Red Task", 100, NULL, 2, NULL);
	xTaskCreate(YEL_CRL, "Yellow Task", 100, NULL, 4, NULL);
	xTaskCreate(GRN_CRL, "Green Task", 100, NULL, 4, NULL);
}

void	vSenderTask(void *pvParameters)
{
	BaseType_t QUE_STS_1;
	int32_t valueToSend = 0;
	pinMode(RED_BTN, INPUT);
	pinMode(YEL_BTN, INPUT);
	pinMode(GRN_BTN, INPUT);
  unsigned long int TIMER = 0;
  int LST_GRN_ST;
  int LST_YEL_ST;

	while(true)
	{
		valueToSend = 0;
		if(digitalRead(RED_BTN) == 1)
		{
			valueToSend += 1;
		}
    if(digitalRead(YEL_BTN) == 0)
      LST_YEL_ST = 0;
		if(digitalRead(YEL_BTN) == 1 && millis() >= TIMER)
		{
      if(LST_YEL_ST == 0)
			  valueToSend += 2;
      LST_YEL_ST = 1;
      TIMER = millis() + 100;
		}
    if(digitalRead(GRN_BTN) == 0)
      LST_GRN_ST = 0;
		if(digitalRead(GRN_BTN) == 1)
		{
      if(LST_GRN_ST == 0)
			  valueToSend += 4;
      LST_GRN_ST = 1;
		}
    //Serial.println("SEND");
    //Serial.println(valueToSend);
		QUE_STS_1 = xQueueSend(SWT_QUE, &valueToSend, 0);
		vTaskDelay(10);
	}
}

void	vReceiverTask(void *pvParameters)
{
	int32_t			valueReceived;
	int32_t			toSend = 0;
	BaseType_t	QUE_STS_1;
	BaseType_t	QUE_STS_RED;
	BaseType_t	QUE_STS_YEL;
	BaseType_t	QUE_STS_GRN;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
	while(true)
	{
		xQueueReceive(SWT_QUE, &valueReceived, xTicksToWait);
    //Serial.println("RECE");
    //Serial.println(valueReceived);
		if(valueReceived % 2 == 1)
		{
			toSend = 1;
			QUE_STS_RED = xQueueSend(RED_QUE, &toSend, 0);
      //Serial.println("Red Sent");
		}
		if(valueReceived == 2 || valueReceived == 3 || valueReceived == 6 || valueReceived == 7)
		{
			toSend = 1;
			QUE_STS_YEL = xQueueSend(YEL_QUE, &toSend, 0);
		}
		if(valueReceived == 4 || valueReceived == 5 || valueReceived == 6 || valueReceived == 7)
		{
			toSend = 1;
			QUE_STS_GRN   = xQueueSend(GRN_QUE, &toSend, 0);
		}
		vTaskDelay(10);
	}
}

void	RED_CRL(void *pvParameters)
{
	int32_t			valueReceived = 0;
	BaseType_t	STS;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
	unsigned long int TIMER;
	
	pinMode(RED, OUTPUT);
	while(true)
	{
		xQueueReceive(RED_QUE, &valueReceived, xTicksToWait);
    //Serial.println(valueReceived);
		if(valueReceived == 1)
		{
      Serial.println("RED_ATV");
			TIMER = millis() + 3000;
			digitalWrite(RED, HIGH);
		}
		if(millis() >= TIMER)
		{
      //Serial.println("Switch off");
			digitalWrite(RED, LOW);
		}
    valueReceived = 0;
	}
}

void	YEL_CRL(void *pvParameters)
{
	int32_t			valueReceived;
	BaseType_t	STS;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
	bool				ST = false;
  unsigned long int TIMER = 0;
	
	pinMode(YEL, OUTPUT);
	while(true)
	{
		xQueueReceive(YEL_QUE, &valueReceived, xTicksToWait);
		if(valueReceived == 1)
		{
      Serial.println("YEL_ATV");
			ST = !ST;
		}
		if(ST == true && millis() >= TIMER)
		{
			digitalWrite(YEL, !digitalRead(YEL));
      TIMER = millis() + 500;
		}
		if(ST == false)
			digitalWrite(YEL, LOW);
    valueReceived = 0;
	}
}

void	GRN_CRL(void *pvParameters)
{
	int32_t			valueReceived;
	BaseType_t	STS;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
	bool				ST = false;
  unsigned long int TIMER_G = 0;
  int count = 0;
	
	pinMode(GRN, OUTPUT);
	while(true)
	{
		xQueueReceive(GRN_QUE, &valueReceived, xTicksToWait);
		if(valueReceived == 1)
		{
      Serial.println("GRN_ATV");
      if(ST == false)
			  ST = true;
      else
        valueReceived = 0;
		}
		if(ST == true && millis() >= TIMER_G)
		{
			digitalWrite(GRN, !digitalRead(GRN));
			TIMER_G = millis() + 500;
      count++;
      if(count >= 4)
      {
        digitalWrite(GRN, LOW);
			  ST = false;
        count = 0;
      }
		}
   valueReceived = 0;
	}
}

void  loop(void)
{
}
