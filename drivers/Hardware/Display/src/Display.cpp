#ifndef DISPLAY_C_
#define DISPLAY_C_

#include "Display.h"
#include <memory>


/**

    @brief Constructor for the Display class that initializes a Display object with a given set of GPIO pins.
    @param a_GPIOS_list A DisplayGPIOS struct containing the GPIO pins for the display.

*/
Display::Display(DisplayGPIOS a_GPIOS_list):gpio_list(a_GPIOS_list)
{

    this->scroll_down_button = std::make_unique<Button>(gpio_list.GPIO_scrollDown);
    this->scroll_up_button = std::make_unique<Button>(gpio_list.GPIO_ScrollUp);
    this->confirm_button = std::make_unique<Button>(gpio_list.GPIO_Confirm);
    this->scroll = std::make_unique<Scroll>();


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

/**

    @brief Initializes the communication interface for the display using the I2C protocol

    @return esp_err_t Returns ESP_OK if the initialization was successful, otherwise returns an error code.
*/
esp_err_t Display::communication_Init()
{
    esp_err_t ret_val;

	i2c_config_t i2c_config = {
				I2C_MODE_MASTER,
				this->gpio_list.GPIO_SDA,
				this->gpio_list.GPIO_SCL,
				GPIO_PULLUP_ENABLE,
				GPIO_PULLUP_ENABLE,
				1000000
	};

	ret_val = i2c_param_config(I2C_NUM_0, &i2c_config);

    if(ESP_OK == ret_val)
	    ret_val = i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);

    return ret_val;
}

/**
    @brief Initializes hardware of the OLED display using I2C communication protocol.

    @return esp_err_t Returns ESP_OK on success, or an error code otherwise.
    */
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

/**

    @brief Displays text on the OLED display at the specified page.

    @param arg_text The text to be displayed on the OLED display.

    @param a_cur_page The page at which the text is to be displayed. Default value of the parameter is set to 0.

    This function takes in a string of text and displays it on the OLED display.
    The text is displayed at the specified page. If a new line character is found
    in the text, the text is displayed on a new page below the current page.

    @note This function uses the font8x8_basic_tr font to display text.

    @return void
    */
template <class T>
void Display::display_Text(T arg_text, uint8_t a_cur_page)
{
    char *text = (char*)arg_text;
	uint8_t text_len = strlen(text);

    i2c_cmd_handle_t cmd;

	uint8_t cur_page = a_cur_page;

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

/**

    @brief Clears the display by filling the entire display with zeros.
    @param none
    This function writes zeros to every byte in the OLED display memory,
    effectively clearing the display. It first creates a zero buffer of 132 bytes,
    one for each column in the display plus one extra byte for padding. Then it
    writes this buffer to every page in the display, starting at page 0 and ending
    at page 7. Finally, it resets the column and page to the top-left corner of the
    display by writing the appropriate control bytes.

    @return void
*/
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

/**

    @brief Restarts the ESP32 device after logging an error message.
    This function logs the given error message using ESP_LOGE, and then calls the esp_restart() function to restart the ESP32 device.
    @param a_error_text The error message to log.

    @return void
    */
void Display::restart_esp(const char * a_error_text) const noexcept
{
		ESP_LOGE(TAG, "ERROR MSG");
        ESP_LOGE(TAG, "ESP RESTART WILL BE PERFORMED");
        esp_restart();
}

/**

    @brief Displays the current state and GPIO pins of the buttons
    This method prints to the standard output stream the current state and GPIO pins of the buttons.
    Specifically, it prints the state and GPIO of the scroll down, scroll up, and confirm buttons.
    @param none

    @return void
    */
void Display::show_button_output() const noexcept
{
		std::cout << "DOWN STATE: " <<static_cast<int>(scroll_down_button->get_button_state()) << " DOWN GPIO: " <<scroll_down_button->get_button_GPIO()<< std::endl;
		std::cout << "UP  STATE: " << static_cast<int>(scroll_up_button->get_button_state())<< "UP GPIO: " <<scroll_up_button->get_button_GPIO() << std::endl;
		std::cout << "CONFIRM  STATE: " << static_cast<int>(confirm_button->get_button_state()) << "CONFIRM GPIO: " <<confirm_button->get_button_GPIO()<< std::endl;

}

int Display::cut_index_helper(int pag, int IDX = 0)
{
    return abs((pag + IDX) % scroll->get_option_count()); //TODO: Handle negative values properly
}

void Display::display_Scroll()
{
    for(uint8_t page = FIRSTROW; page < LASTROW; page++)
    {
        this->display_Text(scroll->options[cut_index_helper(page, scroll->getCurrentOption())].c_str(), page);
    }
}

void Display::scroll_up()
{
    scroll->scrollUp();
}

void Display::scroll_down()
{
    scroll->scrollDown();
}

void Display::action_confirm()
{
    std::stringstream action_mess;

    action_mess << "Number: " << cut_index_helper(scroll->getCurrentOption());
    this->display_Text(action_mess.str().c_str());
}

bool Display::is_scroll_down_pressed () const noexcept
{
    return scroll_down_button->get_button_state() != HIGH;
}

bool Display::is_scroll_up_pressed () const noexcept
{
    return scroll_up_button->get_button_state() != HIGH;
}

bool Display::is_confirm_pressed () const noexcept
{
    return confirm_button->get_button_state() != HIGH;
}

#endif
