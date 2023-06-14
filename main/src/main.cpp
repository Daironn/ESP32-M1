#include "main.h"

#include "esp_event_loop.h"
#include "esp_wifi.h"
#include "nvs_flash.h"


void scan()
{
    wifi_scan_config_t scan_config =
    {
        .ssid = 0,
        .bssid = 0,
        .channel = 0,
        .show_hidden = TRUE
    };
    
    esp_wifi_scan_start(&scan_config, true);

    uint16_t ap_num;
    wifi_ap_record_t ap_records[20];
    esp_wifi_scan_get_ap_records(&ap_num, ap_records);
    std::cout << "Scanned wifis: \n";
    for(uint i =0; i < ap_num; i++)
    {
        std::cout << "ID"<< i << "\n";
        std::cout << ap_records[i].ssid;
    }   
}

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    tcpip_adapter_init();

    wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

  // while (1)
  // {
     // vTaskDelay(3000 / 10);
    scan();
  // }
  
}
