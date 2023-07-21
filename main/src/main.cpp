#include "main.h"

#include "esp_event.h"
#include "esp_wifi.h"
#include "nvs_flash.h"

#include "Button.h"
#include "GPIOController.h"
#include "Display.h"
#include "Scroll.h"

#include "bsoncxx/v_noabi/bsoncxx/builder/stream/document.hpp"
#include "bsoncxx/v_noabi/bsoncxx/json.hpp"
#include "bsoncxx/v_noabi/bsoncxx/oid.hpp"
#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include "mongocxx/v_noabi/mongocxx/database.hpp"
#include "mongocxx/v_noabi/mongocxx/uri.hpp"

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
