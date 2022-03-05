#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "tFast.h"

TaskHandle_t Task1, Task2 = NULL;

extern "C" int app_main(void)
{
    xTaskCreate(tFast, "tFast", 4098*8, NULL, 1, &Task1);

    return EXIT_SUCCESS;
}
