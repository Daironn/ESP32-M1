/**
 * @file gpio_controller.h
 * @brief Defines a GPIOController class that represents a hardware GPIO pin.
 */

#ifndef GPIOCONTROLLER_H_
#define GPIOCONTROLLER_H_

#include "driver/gpio.h"

/**
 * 
 * @def HIGH 
 * @brief Represents a GPIO pin state HIGH.
 */
#define HIGH 1

/**
 * 
 * @def LOW 
 * @brief Represents a GPIO pin state LOW.
 */
#define LOW  0

/**
 * @brief Represents a hardware GPIO pin.
 */
class GPIOController
{
private:
    gpio_num_t GPIO_number; /**< The GPIO pin number. */
    gpio_mode_t GPIO_direction; /**< The GPIO pin direction. */

public:
    /**
     * @brief Constructs a new GPIOController instance.
     * @param gpio_num The GPIO pin number to control.
     */
    GPIOController(gpio_num_t);

    /**
     * @brief Destructs the GPIOController instance.
     * 
     * The destructor is set to the default implementation.
     */
    ~GPIOController() = default;

public:
    /**
     * @brief Gets the current state of the GPIO pin.
     * @return The current state of the GPIO pin, either HIGH or LOW.
     */
    uint8_t get_GPIO_state() const;

    /**
     * @brief Gets the direction of the GPIO pin.
     * @return The direction of the GPIO pin, either GPIO_MODE_INPUT or GPIO_MODE_OUTPUT.
     */
    gpio_mode_t get_GPIO_direction() const;
    
public:
    /**
     * @brief Sets the state of the GPIO pin.
     * @param state The state to set the GPIO pin to, either HIGH or LOW.
     */
    void set_GPIO_state(uint8_t state);

    /**
     * @brief Sets the direction of the GPIO pin.
     * @param direction The direction to set the GPIO pin to, either GPIO_MODE_INPUT or GPIO_MODE_OUTPUT.
     */
    void set_GPIO_direction(gpio_mode_t);
};

#endif
