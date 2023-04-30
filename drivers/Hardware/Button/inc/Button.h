#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"

class Button
{
private:
    /* data */
public:
    Button(/* args */);
    ~Button();
};

Button::Button(/* args */)
{
}

Button::~Button()
{
}
