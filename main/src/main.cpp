#include "main.h"

#include "esp_event.h"
#include "esp_wifi.h"
#include "nvs_flash.h"

#include "Button.h"
#include "GPIOController.h"
#include "Display.h"
#include "Scroll.h"


#include "WiFiManager.h"

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    tcpip_adapter_init();


    WiFiManager obj;
    obj.init();
    obj.begin();

    std::cout << (int)obj._state;
}
