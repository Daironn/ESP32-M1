#include "WiFiManager.h"
#include <iostream>
// Wifi statics

void WiFiManager::event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (WIFI_EVENT == event_base)
    {
        return wifi_event_handler(arg, event_base, event_id, event_data);
    }
    else if (IP_EVENT == event_base)
    {
        return ip_event_handler(arg, event_base, event_id, event_data);
    }
    else
    {
        ESP_LOGE(_log_tag, "%s:%d Unexpected event: %s", __func__, __LINE__, event_base);
    }
}

void WiFiManager::wifi_event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (WIFI_EVENT == event_base)
    {
        const wifi_event_t event_type{static_cast<wifi_event_t>(event_id)};

        switch(event_type)
        {
        case WIFI_EVENT_STA_START:
        {
            std::lock_guard<std::mutex> state_guard(state_mutx);
            _state = state_e::READY_TO_CONNECT;
            break;
        }

        case WIFI_EVENT_STA_CONNECTED:
        {
            std::lock_guard<std::mutex> state_guard(state_mutx);
            _state = state_e::WAITING_FOR_IP;
            break;
        }

        default:
            ESP_LOGW(_log_tag, "%s:%d Default switch case (%d)", __func__, __LINE__, event_id);
            break;
        }
    }
}

void WiFiManager::ip_event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (IP_EVENT == event_base)
    {
        const ip_event_t event_type{static_cast<ip_event_t>(event_id)};

        switch(event_type)
        {
        case IP_EVENT_STA_GOT_IP:
        {
            std::lock_guard<std::mutex> guard(state_mutx);
            _state = state_e::CONNECTED;
            break;
        }

        case IP_EVENT_STA_LOST_IP:
        {
            std::lock_guard<std::mutex> guard(state_mutx);
            _state = state_e::WAITING_FOR_IP;
            break;
        }

        default:
            ESP_LOGW(_log_tag, "%s:%d Default switch case (%d)", __func__, __LINE__, event_id);
            break;
        }
    }
}



esp_err_t WiFiManager::init(void)
{
    return _init();
}

esp_err_t WiFiManager::begin(void)
{
    std::lock_guard<std::mutex> connect_guard(connect_mutx);
    esp_err_t status{ESP_OK};
    std::lock_guard<std::mutex> state_guard(state_mutx);
    
    switch(_state)
    {
    case state_e::READY_TO_CONNECT:
        status = esp_wifi_connect();

        if (ESP_OK == status)
            _state = state_e::CONNECTING;

        break;
    case state_e::CONNECTING:
    case state_e::WAITING_FOR_IP:
    case state_e::CONNECTED:
        break;
    case state_e::NOT_INITIALISED:
    case state_e::INITIALISED:
    case state_e::DISCONNECTED:
    case state_e::ERROR:
        status = ESP_FAIL;
        break;
    }

    return status;
}

esp_err_t WiFiManager::_init(void)
{
    std::lock_guard<std::mutex> init_guard(init_mutx);

    esp_err_t status{ESP_OK};

    std::lock_guard<std::mutex> state_guard(state_mutx);


    if (state_e::NOT_INITIALISED == _state)
    {
        status = esp_netif_init();

        if (ESP_OK == status)
        {
            const esp_netif_t* const p_netif = esp_netif_create_default_wifi_sta();
            if (!p_netif) status = ESP_FAIL;
        }
        std::cout << status << std::endl;
        if (ESP_OK == status)
        {
            status = esp_wifi_init(&wifi_init_config);
            std::cout << status<< std::endl;
        }
        if (ESP_OK == status)
        {
            status = esp_event_loop_create_default();
            std::cout << status<< std::endl;
        }
        if (ESP_OK == status)
        {
            status = esp_event_handler_register(WIFI_EVENT,
                                                            ESP_EVENT_ANY_ID,
                                                            &wifi_event_handler,
                                                            nullptr
                                                            );

        }
        std::cout << status<< std::endl;
        if (ESP_OK == status)
        {
            status = esp_event_handler_register(IP_EVENT,
                                                            ESP_EVENT_ANY_ID,
                                                            &ip_event_handler,
                                                            nullptr
                                                            );

        }
        std::cout << status<< std::endl;
        if (ESP_OK == status)
        {
            status = esp_wifi_set_mode(WIFI_MODE_STA);

        }
        std::cout << status<< std::endl;
        if (ESP_OK == status)
        {
            const size_t ssid_len_to_copy       = std::min(strlen(ssid), 
                                                    sizeof(wifi_config.sta.ssid));

            memcpy(wifi_config.sta.ssid, ssid, ssid_len_to_copy);
            
            const size_t password_len_to_copy   = std::min(strlen(password),
                                                    sizeof(wifi_config.sta.password));
       
            memcpy(wifi_config.sta.password, password, password_len_to_copy);

            wifi_config.sta.threshold.authmode  = WIFI_AUTH_WPA2_PSK;
            wifi_config.sta.pmf_cfg.capable     = true;
            wifi_config.sta.pmf_cfg.required    = false;

            status = esp_wifi_set_config(WIFI_IF_STA, &wifi_config);

        }
        
        if (ESP_OK == status)
        {
            status = esp_wifi_start();

        }

        if (ESP_OK == status)
        {
            _state = state_e::INITIALISED;
        }
    }
    else if (state_e::ERROR == _state)
    {
        status = ESP_FAIL;
    }

    return status;
}
