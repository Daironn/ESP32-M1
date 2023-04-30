#include <stdio.h>
#include <iostream>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "driver/gpio.h"

#define GPIO_BIT_MASK  ((1ULL<<GPIO_NUM_18)) 

extern "C" void app_main(void)
{
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_18, GPIO_MODE_INPUT);
    gpio_set_pull_mode(GPIO_NUM_18, GPIO_PULLUP_ONLY);
    while (true)
    {
        std::cout << gpio_get_level(GPIO_NUM_18) << "\n";

        if(gpio_get_level(GPIO_NUM_18) == 0)
        {
            gpio_set_level(GPIO_NUM_2, 1);
        }
        else
        {
            gpio_set_level(GPIO_NUM_2, 0);
        }
        vTaskDelay(10);
    }
    
}
