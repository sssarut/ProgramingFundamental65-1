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


