/**
 * @file Button.h
 * @brief Defines a Button class that represents a hardware button connected to a GPIO pin.
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <driver/gpio.h>

#define HIGH 1
#define LOW 0

/**
 * @brief Represents a hardware button connected to a GPIO pin.
 */
class Button
{
public:
    /**
     * @brief Constructs a new Button instance.
     * @param gpio_num The GPIO pin number that the button is connected to.
     */
    Button(gpio_num_t) noexcept;

    /**
     * @brief Destructs the Button instance.
     * 
     * The destructor is set to the default implementation.
     */
    ~Button() = default;

public:
    /**
     * @brief Gets the current state of the button.
     * @return The current state of the button, either HIGH or LOW.
     */
    uint8_t get_button_state() const noexcept;

    /**
     * @brief Gets the GPIO pin number that the button is connected to.
     * @return The GPIO pin number that the button is connected to.
     */
    gpio_num_t get_button_GPIO() const noexcept;

private:
    gpio_num_t GPIO_number; /**< The GPIO pin number that the button is connected to. */
};

#endif /* BUTTON_H */
