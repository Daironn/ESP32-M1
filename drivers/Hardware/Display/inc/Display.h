/**
 * @file Display.h
 * @brief Defines the Display class and its dependencies.
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <iostream>
#include <cstring>


#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "esp_system.h"

#include "DisplaySettings.h"
#include "Button.h"

/**

    @def TAG
    @brief A string identifier for the SH1106 driver.
*/
#define TAG "SH1106"

/**

    @def TRUE
    @brief A macro for the boolean value true.
*/
#define TRUE true

/**

    @def FALSE
    @brief A macro for the boolean value false.
*/
#define FALSE false


/**
 * @brief Contains the GPIO pin numbers used by the display.
 */
struct DisplayGPIOS
{
    gpio_num_t GPIO_SDA;        /**< The GPIO pin number used for the SDA signal. */
    gpio_num_t GPIO_SCL;        /**< The GPIO pin number used for the SCL signal. */
    gpio_num_t GPIO_ScrollUp;   /**< The GPIO pin number used for the scroll up button. */
    gpio_num_t GPIO_scrollDown; /**< The GPIO pin number used for the scroll down button. */
    gpio_num_t GPIO_Confirm;    /**< The GPIO pin number used for the confirm button. */
};

/**
 * @brief Controls an OLED display using the ESP32.
 */
class Display
{
private:
    DisplayGPIOS gpio_list;     /**< The GPIO pin numbers used by the display. */

    Button * scroll_down_button; /**< The scroll down button. */
    Button * scroll_up_button;   /**< The scroll up button. */
    Button * confirm_button;     /**< The confirm button. */

private:
    /**
     * @brief Initializes the communication interface used by the display.
     * @return An ESP error code indicating whether the initialization was successful.
     */
    esp_err_t communication_Init();

    /**
     * @brief Initializes the hardware used by the display.
     * @return An ESP error code indicating whether the initialization was successful.
     */
    esp_err_t display_Hardware_Init();

private:
    /**
     * @brief Restarts the ESP.
     * @param msg A message to display before the ESP restarts.
     */
    void restart_esp(const char *);

public:
    /**
     * @brief Displays text on the OLED display.
     * @param text The text to display.
     * @param a_cur_page The page to display the text on.
     */
    void display_Text(const char *, uint8_t a_cur_page = 0);

    /**
     * @brief Clears the OLED display.
     */
    void display_Clear();

public:
    /**
     * @brief Constructs a new Display instance.
     * @param gpio_list The GPIO pin numbers used by the display.
     */
    Display(DisplayGPIOS);

    /**
     * @brief Destroys the Display instance.
     */
    ~Display();

public:
    /**
     * @brief Shows the output of the buttons on the OLED display.
     */
    void show_button_output() const;
};

#endif
