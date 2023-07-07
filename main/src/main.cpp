#include "main.h"

#include "esp_event_loop.h"
#include "esp_wifi.h"
#include "nvs_flash.h"

#include "Button.h"
#include "GPIOController.h"
#include "Display.h"
#include "Scroll.h"
#include "WifiManager.h"


#define  STA_SSID "TEST"
#define  STA_PASS "TEST"
// void scan()
// {
//     wifi_scan_config_t scan_config =
//     {
//         .ssid = 0,
//         .bssid = 0,
//         .channel = 0,
//         .show_hidden = TRUE
//     };
    
//     esp_wifi_scan_start(&scan_config, true);

//     uint16_t ap_num;
//     wifi_ap_record_t ap_records[20];
//     esp_wifi_scan_get_ap_records(&ap_num, ap_records);
//     std::cout << "Scanned wifis: \n";
//     for(uint i =0; i < ap_num; i++)
//     {
//         std::cout << "ID"<< i << "\n";
//         std::cout << ap_records[i].ssid;
//     }   
// }

extern "C" void app_main(void)
{
    // ESP_ERROR_CHECK(nvs_flash_init());
    // tcpip_adapter_init();

    // wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
    // ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));

    // // scan();

    // ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

    // wifi_config_t sta_config =
    // {
    //     .sta =
    //     {
    //         STA_SSID,STA_PASS
    //     },
    // };

    // ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &sta_config));


    // ESP_ERROR_CHECK(esp_wifi_start());
    // ESP_ERROR_CHECK(esp_wifi_connect());
    // ESP_ERROR_CHECK(esp_wifi_disconnect());
}
