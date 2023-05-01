#include "GPIOController.h"

GPIOController::GPIOController(gpio_num_t a_GPIO_number):GPIO_number(a_GPIO_number)
{
}

uint8_t GPIOController::get_GPIO_state() const
{
    return gpio_get_level(GPIO_number);
}

gpio_mode_t GPIOController::get_GPIO_direction() const
{
    return GPIO_direction;
}

void GPIOController::set_GPIO_state(uint8_t a_level)
{
    gpio_set_level(GPIO_number, a_level);
}

void GPIOController::set_GPIO_direction(gpio_mode_t a_direction)
{
    GPIO_direction = a_direction;
    gpio_set_direction(GPIO_number, GPIO_direction);
}
