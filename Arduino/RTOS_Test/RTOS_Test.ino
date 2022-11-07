#include <Arduino_FreeRTOS.h>
#include "queue.h"

# define RED 8
# define YEL 9
# define GRN 10

# define RED_BTN  1
# define YEL_BTN  2
# define GRN_BTN  3

QueueHandle_t RED_QUE;
QueueHandle_t YEL_QUE;
QueueHandle_t GRN_QUE;
QueueHandle_t SWT_QUE;

void	setup(void)
{
	Serial.begin(9600);
	SWT_QUE = xQueueCreate(10, sizeof(int32_t));

	xTaskCreate(vSenderTask, "Sender Task", 100, NULL, 3, NULL);
	xTaskCreate(vReceiverTask, "Receiver Task", 100, NULL, 3, NULL);
	xTaskCreate(RED_CRL, "Red Task", 100, NULL, 2, NULL);
	xTaskCreate(YEL_CRL, "Yellow Task", 100, NULL, 2, NULL);
	xTaskCreate(GRN_CRL, "Green Task", 100, NULL, 2, NULL);
}

void	vSenderTask(void *pvParameters)
{
	BaseType_t QUE_STS_1;
	int32_t valueToSend = 0;
	pinMode(RED_BTN, INPUT);
	pinMode(YEL_BTN, INPUT);
	pinMode(GRN_BTN, INPUT);

	while(true)
	{
		valueToSend = 0;
		if(digitalRead(RED_BTN) == true)
		{
			valueToSend += 1;
		}
		if(digitalRead(YEL_BTN) == true)
		{
			valueToSend += 2;
		}
		if(digitalRead(GRN_BTN) == true)
		{
			valueToSend += 4;
		}
		QUE_STS_1 = xQueueSend(SWT_QUE, &valueToSend, 0);
		vTaskDelay(10);
	}
}

void	vReceiverTask(void *pvParameters)
{
	int32_t			valueReceived;
	int32_t			toSend;
	BaseType_t	QUE_STS_1;
	BaseType_t	QUE_STS_RED;
	BaseType_t	QUE_STS_YEL;
	BaseType_t	QUE_STS_GRN;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
	while(true)
	{
		xQueueReceive(SWT_QUE, &valueReceived, xTicksToWait);
		if(valueReceived % 2 == 1)
		{
			toSend = 1;
			QUE_STS_RED = xQueueSend(RED_QUE, &toSend, 0);
		}
		if(valueReceived == 2 || valueReceived == 3 || valueReceived == 6 || valueReceived == 7)
		{
			toSend = 1;
			QUE_STS_YEL = xQueueSend(YEL_QUE, &toSend, 0);
		}
		if(valueReceived == 4 || valueReceived == 5 || valueReceived == 6 || valueReceived == 7)
		{
			toSend = 1;
			QUE_STS_GRN = xQueueSend(GRN_QUE, &toSend, 0);
		}
		vTaskDelay(10);
	}
}

void	RED_CRL(void *pvParameters)
{
	int32_t			valueReceived;
	BaseType_t	STS;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
	unsigned long int TIMER;
	
	pinMode(RED, OUTPUT);
	while(true)
	{
		xQueueReceive(RED_QUE, &valueReceived, xTicksToWait);
		if(valueReceived == 1)
		{
			TIMER = millis() + 3000;
			digitalWrite(RED, HIGH);
		}
		if(millis >= TIMER)
		{
			digitalWrite(RED, LOW);
		}
	}
}

void	YEL_CRL(void *pvParameters)
{
	int32_t			valueReceived;
	BaseType_t	STS;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
	bool				ST = false;
	
	pinMode(YEL, OUTPUT);
	while(true)
	{
		xQueueReceive(YEL_QUE, &valueReceived, xTicksToWait);
		if(valueReceived == 1)
		{
			ST = !ST;
		}
		if(ST == true)
		{
			digitalWrite(YEL, !digitalRead(YEL));
			vTaskDelay(500);
		}
		if(ST == false)
			digitalWrite(YEL, LOW);
	}
}

void	GRN_CRL(void *pvParameters)
{
	int32_t			valueReceived;
	BaseType_t	STS;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
	bool				ST = false;
	
	pinMode(GRN, OUTPUT);
	while(true)
	{
		xQueueReceive(GRN_QUE, &valueReceived, xTicksToWait);
		if(valueReceived == 1 && ST == false)
		{
			ST = true;
		}
		if(ST == true)
		{
			digitalWrite(GRN, !digitalRead(GRN));
			vTaskDelay(500);
			digitalWrite(GRN, !digitalRead(GRN));
			vTaskDelay(500);
			digitalWrite(GRN, !digitalRead(GRN));
			vTaskDelay(500);
			digitalWrite(GRN, !digitalRead(GRN));
			vTaskDelay(500);
			digitalWrite(GRN, !digitalRead(GRN));
			vTaskDelay(500);
			digitalWrite(GRN, !digitalRead(GRN));
			vTaskDelay(500);
			digitalWrite(GRN, LOW);
			ST = false;
		}
	}
}

void  loop(void)
{
  int i = 1;
}
