// Library headers
#include <stdio.h>
#include <iostream>

// Driver Fheaders
#include "Button.h"
#include "GPIOController.h"

// RTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

extern "C" void app_main(void)
{
    Button inputButton(GPIO_NUM_18);
    GPIOController blueLed(GPIO_NUM_2);

    blueLed.set_GPIO_direction(GPIO_MODE_OUTPUT);

    while (true)
    {
        if(inputButton.get_button_state() == LOW)
        {
            blueLed.set_GPIO_state(HIGH);
        }
        else
        {
            blueLed.set_GPIO_state(LOW);
        }
        vTaskDelay(10);
    }
    
}
