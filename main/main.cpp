#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "MAX6675.h"

extern "C" int app_main(void)
{
    MAX6675 temp(5);
    
    // Initialise the xLastWakeTime variable with the current time.
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = 1000 / portTICK_PERIOD_MS; // 1ms 

    for( ;; )
    {
        // Wait for the next cycle.
        vTaskDelayUntil( &xLastWakeTime, xFrequency );

        // Perform action here.
        temp.ReadTemperatureCelcius();
    }

    return EXIT_SUCCESS;
}
