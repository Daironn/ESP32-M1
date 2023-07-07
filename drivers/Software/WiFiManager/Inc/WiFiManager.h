#pragma once

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

#include <algorithm>
#include <mutex>

#include <cstring>

class Wifi
{
    constexpr static const char* _log_tag{"WiFi"};
    constexpr static const char* ssid{"GreenGiant-TEST"};
    constexpr static const char* password{"GreenGiant"};

public:

    enum class state_e
    {
        NOT_INITIALISED,
        INITIALISED,
        READY_TO_CONNECT,
        CONNECTING,
        WAITING_FOR_IP,
        CONNECTED,
        DISCONNECTED,
        ERROR
    };


    Wifi(void) = default;
    ~Wifi(void) = default;

    esp_err_t init(void);
    esp_err_t begin(void);

    constexpr const state_e& get_state(void) { return _state; }

private:
    static esp_err_t _init(void);
    static wifi_init_config_t wifi_init_config;
    static wifi_config_t wifi_config;

    static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data);
    static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data);
    static void ip_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data);

    static state_e _state;

    static std::mutex connect_mutx; ///< Connect mutex
    static std::mutex state_mutx;   ///< State change mutex
};
