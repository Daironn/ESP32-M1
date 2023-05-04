/**
 * @file Button.cpp
 * @brief Defines the implementation of the Button class.
 */

#include "Button.h"

/**
 * @brief Constructs a new Button instance.
 * @param a_GPIO_number The GPIO pin number that the button is connected to.
 * 
 * Initializes the GPIO pin as an input with a pull-up resistor.
 */
Button::Button(gpio_num_t a_GPIO_number) : GPIO_number(a_GPIO_number)
{
    gpio_set_direction(GPIO_number, GPIO_MODE_INPUT);
    gpio_set_pull_mode(GPIO_number, GPIO_PULLUP_ONLY);
}

/**
 * @brief Gets the current state of the button.
 * @return The current state of the button, either HIGH or LOW.
 */
uint8_t Button::get_button_state() const
{
    return gpio_get_level(GPIO_number);
}

/**
 * @brief Gets the GPIO pin number that the button is connected to.
 * @return The GPIO pin number that the button is connected to.
 */
gpio_num_t Button::get_button_GPIO() const
{
    return GPIO_number;
}
