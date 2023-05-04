#ifndef DISPLAY_H
#define DISPLAY_H

#include<iostream>
#include<cstring>

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "esp_system.h"

#include "DisplaySettings.h"
#include "FontSettings.h"

#define TAG "SH1106"
#define TRUE true
#define FALSE false

class Display
{
private:
    gpio_num_t GPIO_SDA;
    gpio_num_t GPIO_SCL;

private:
    esp_err_t communication_Init();
    esp_err_t display_Hardware_Init();

private:
    void restart_esp(const char *);
public:

    void display_Text(const char *);
    void display_Clear();
public:
    Display(gpio_num_t, gpio_num_t);
    ~Display() = default;

};

#endif
