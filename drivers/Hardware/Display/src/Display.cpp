#ifndef DISPLAY_C
#define DISPLAY_C

#include "Display.h"

Display::Display(gpio_num_t a_GPIO_SDA, gpio_num_t a_GPIO_SCL):GPIO_SDA(a_GPIO_SDA),GPIO_SCL(a_GPIO_SCL) 
{
    esp_err_t ret_val_master = this->communication_Init();
    esp_err_t ret_val_hardware = this->display_Hardware_Init();
    vTaskDelay(1000/portTICK_PERIOD_MS);

    if(ESP_OK == ret_val_master && ESP_OK == ret_val_hardware)
    {
        this->display_Clear();
    }
    else
    {
        this->restart_esp("ERROR OCCURED DURING OLED CONFIGURATION");
    }

}

void Display::restart_esp(const char * a_error_text)
{
		ESP_LOGE(TAG, "ESP RESTART WILL BE PERFORMED");
        ESP_LOGE(TAG, "ESP RESTART WILL BE PERFORMED");
        esp_restart();
}

esp_err_t Display::communication_Init()
{
    esp_err_t ret_val;

	i2c_config_t i2c_config = {
				I2C_MODE_MASTER,
				this->GPIO_SDA,
				this->GPIO_SCL,
				GPIO_PULLUP_ENABLE,
				GPIO_PULLUP_ENABLE,
				1000000
	};

	ret_val = i2c_param_config(I2C_NUM_0, &i2c_config);

    if(ESP_OK == ret_val)
	    ret_val = i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);

    return ret_val;
}

esp_err_t Display::display_Hardware_Init()
{

    esp_err_t ret_val;

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();

	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (OLED_I2C_ADDRESS << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, OLED_CONTROL_BYTE_CMD_STREAM, true);

	i2c_master_write_byte(cmd, OLED_CMD_SET_CHARGE_PUMP_CTRL, true);
	i2c_master_write_byte(cmd, OLED_CMD_SET_CHARGE_PUMP_ON, true);

	i2c_master_write_byte(cmd, OLED_CMD_SET_SEGMENT_REMAP_INVERSE, true); // reverse left-right mapping
	i2c_master_write_byte(cmd, OLED_CMD_SET_COM_SCAN_MODE_REVERSE, true); // reverse up-bottom mapping

	i2c_master_write_byte(cmd, OLED_CMD_DISPLAY_ON, true);

	i2c_master_write_byte(cmd, 0x00, true); // reset column low bits
	i2c_master_write_byte(cmd, 0x10, true); // reset column high bits
	i2c_master_write_byte(cmd, 0xB0, true); // reset page
    i2c_master_write_byte(cmd, 0x40, true); // set start line
    i2c_master_write_byte(cmd, OLED_CMD_SET_DISPLAY_OFFSET, true);
    i2c_master_write_byte(cmd, 0x00, true);

	i2c_master_stop(cmd);

	ret_val = i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
	
	if (ret_val == ESP_OK) {
		ESP_LOGI(TAG, "OLED configured successfully");
	} else {
		ESP_LOGE(TAG, "OLED configuration failed. code: 0x%.2X", ret_val);
	}
	i2c_cmd_link_delete(cmd);

    return ret_val;
}

void Display::display_Text(const char * arg_text)
{
    char *text = (char*)arg_text;
	uint8_t text_len = strlen(text);

	i2c_cmd_handle_t cmd;

	uint8_t cur_page = 0;

	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (OLED_I2C_ADDRESS << 1) | I2C_MASTER_WRITE, true);

	i2c_master_write_byte(cmd, OLED_CONTROL_BYTE_CMD_STREAM, true);
	i2c_master_write_byte(cmd, 0x08, true); 
	i2c_master_write_byte(cmd, 0x10, true);
	i2c_master_write_byte(cmd, 0xB0 | cur_page, true); 

	i2c_master_stop(cmd);
	i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
	i2c_cmd_link_delete(cmd);

	for (uint8_t i = 0; i < text_len; i++) 
	{
		cmd = i2c_cmd_link_create();
		i2c_master_start(cmd);
		i2c_master_write_byte(cmd, (OLED_I2C_ADDRESS << 1) | I2C_MASTER_WRITE, true);

		if (text[i] == '\n') 
		{
			i2c_master_write_byte(cmd, OLED_CONTROL_BYTE_CMD_STREAM, true);
			i2c_master_write_byte(cmd, 0x08, true); 
			i2c_master_write_byte(cmd, 0x10, true);
			i2c_master_write_byte(cmd, 0xB0 | ++cur_page, true); 
		}
		else
		{
			i2c_master_write_byte(cmd, OLED_CONTROL_BYTE_DATA_STREAM, true);
			i2c_master_write(cmd, font8x8_basic_tr[(uint8_t)text[i]], 8, true);		
		}

		i2c_master_stop(cmd);
		i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
		i2c_cmd_link_delete(cmd);
		
	}
}

void Display::display_Clear()
{
    i2c_cmd_handle_t cmd;

	uint8_t zero[132];
    memset(zero, 0, 132);
	for (uint8_t i = 0; i < 8; i++) {
		cmd = i2c_cmd_link_create();
		i2c_master_start(cmd);
		i2c_master_write_byte(cmd, (OLED_I2C_ADDRESS << 1) | I2C_MASTER_WRITE, true);
		i2c_master_write_byte(cmd, OLED_CONTROL_BYTE_CMD_SINGLE, true);
		i2c_master_write_byte(cmd, 0xB0 | i, true);

		i2c_master_write_byte(cmd, OLED_CONTROL_BYTE_DATA_STREAM, true);
		i2c_master_write(cmd, zero, 132, true);
		i2c_master_stop(cmd);
		i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
		i2c_cmd_link_delete(cmd);
	}

    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, OLED_CONTROL_BYTE_CMD_STREAM, true);
    i2c_master_write_byte(cmd, 0x00, true); // reset column
    i2c_master_write_byte(cmd, 0x10, true);
    i2c_master_write_byte(cmd, 0xB0, true); // reset page
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
}

#endif
