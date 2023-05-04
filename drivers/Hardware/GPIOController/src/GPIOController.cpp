/**
 * @file GPIOController.cpp
 * @brief Defines the implementation of the GPIOController class.
 */

#include "GPIOController.h"

/**
 * @brief Constructs a new GPIOController instance.
 * @param a_GPIO_number The GPIO pin number to control.
 */
GPIOController::GPIOController(gpio_num_t a_GPIO_number) : GPIO_number(a_GPIO_number), GPIO_direction(GPIO_MODE_INPUT)
{
}

/**
 * @brief Gets the current state of the GPIO pin.
 * @return The current state of the GPIO pin, either HIGH or LOW.
 */
uint8_t GPIOController::get_GPIO_state() const
{
    return gpio_get_level(GPIO_number);
}

/**
 * @brief Gets the direction of the GPIO pin.
 * @return The direction of the GPIO pin, either GPIO_MODE_INPUT or GPIO_MODE_OUTPUT.
 */
gpio_mode_t GPIOController::get_GPIO_direction() const
{
    return GPIO_direction;
}

/**
 * @brief Sets the state of the GPIO pin.
 * @param a_level The state to set the GPIO pin to, either HIGH or LOW.
 */
void GPIOController::set_GPIO_state(uint8_t a_level)
{
    gpio_set_level(GPIO_number, a_level);
}

/**
 * @brief Sets the direction of the GPIO pin.
 * @param a_direction The direction to set the GPIO pin to, either GPIO_MODE_INPUT or GPIO_MODE_OUTPUT.
 */
void GPIOController::set_GPIO_direction(gpio_mode_t a_direction)
{
    GPIO_direction = a_direction;
    gpio_set_direction(GPIO_number, GPIO_direction);
}
