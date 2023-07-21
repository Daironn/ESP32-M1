#pragma once

#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"

#include <algorithm>
#include <mutex>

#include <cstring>

class WiFiManager
{
    constexpr static const char* _log_tag{"WiFi"};
    constexpr static const char* ssid{"XXX"};
    constexpr static const char* password{"XXX"};

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


    WiFiManager(void) = default;
    ~WiFiManager(void) = default;

    esp_err_t init(void);
    esp_err_t begin(void);

    constexpr const state_e& get_state(void) { return _state; }

private:
    static esp_err_t _init(void);
    inline static wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
    inline static wifi_config_t wifi_config{};

    static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data);
    static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data);
    static void ip_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data);
public:
    inline static state_e _state {state_e::NOT_INITIALISED};
private:
    inline static std::mutex connect_mutx {}; ///< Connect mutex
    inline static std::mutex state_mutx {};   ///< State change mutex
    inline static std::mutex init_mutx {};   ///< State change mutex
};
