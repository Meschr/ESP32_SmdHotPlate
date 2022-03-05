#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "tFast.h"
#include "PidControllerStateMachine.h"

void tFast(void* pvParameters)
{
    CDataLogStateMachine::CreateInstance();

    // Initialise the xLastWakeTime variable with the current time.
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = 1000 / portTICK_PERIOD_MS; // 1000ms 

    for( ;; )
    {
        // Wait for the next cycle.
        vTaskDelayUntil( &xLastWakeTime, xFrequency );

        // Perform action here.
        CDataLogStateMachine::GetInstance()->Send();
    }
}
