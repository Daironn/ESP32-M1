#pragma once
#include "driver/gpio.h"

#define HIGH 1
#define LOW 0

class GPIOController
{
private:
    gpio_num_t GPIO_number;
    gpio_mode_t GPIO_direction;

public:
    GPIOController(gpio_num_t);
    ~GPIOController() = default;

public:
    uint8_t get_GPIO_state() const;
    gpio_mode_t get_GPIO_direction() const;
    
public:
    void set_GPIO_state(uint8_t);
    void set_GPIO_direction(gpio_mode_t);
};
