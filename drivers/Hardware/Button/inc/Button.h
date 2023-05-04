#pragma once
#include "driver/gpio.h"

#define HIGH 1
#define LOW 0

class Button
{
private:
    gpio_num_t GPIO_number;
public:
    Button(gpio_num_t);
    ~Button() = default;

public:
    uint8_t get_button_state() const;
    gpio_num_t get_button_GPIO() const;
};
