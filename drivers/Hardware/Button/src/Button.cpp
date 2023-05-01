#include "Button.h"

Button::Button(gpio_num_t a_GPIO_number):GPIO_number(a_GPIO_number)
{
    gpio_set_direction(GPIO_number, GPIO_MODE_INPUT);
    gpio_set_pull_mode(GPIO_number, GPIO_PULLUP_ONLY);
}

uint8_t Button::get_button_state() const
{
    return gpio_get_level(GPIO_number);
}