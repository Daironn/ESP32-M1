#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <cstring>


#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "esp_system.h"

#include "DisplaySettings.h"
#include "Button.h"

#define TAG "SH1106"
#define TRUE true
#define FALSE false


struct  DisplayGPIOS
{
    gpio_num_t GPIO_SDA;
    gpio_num_t GPIO_SCL;
    gpio_num_t GPIO_ScrollUp;
    gpio_num_t GPIO_scrollDown;
    gpio_num_t GPIO_Confirm;
};

class Display
{
private:
    DisplayGPIOS gpio_list;

    Button * scroll_down_button;
    Button * scroll_up_button;
    Button * confirm_button;

private:
    esp_err_t communication_Init();
    esp_err_t display_Hardware_Init();

private:
    void restart_esp(const char *);

public:

    void display_Text(const char *, uint8_t a_cur_page = 0);
    void display_Clear();
public:
    Display(DisplayGPIOS);
    ~Display();

public:
    void show_button_output() const;
};

#endif
