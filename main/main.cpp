#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Driver Fheaders
#include "Button.h"
#include "GPIOController.h"
#include "Display.h"

extern "C" void app_main(void)
{

	bool wait = true;
	Display display(GPIO_NUM_21, GPIO_NUM_22);

    Button inputButton(GPIO_NUM_18);
    GPIOController blueLed(GPIO_NUM_2);

    blueLed.set_GPIO_direction(GPIO_MODE_OUTPUT);

    while (wait)
    {
        if(LOW == inputButton.get_button_state())
        {
            blueLed.set_GPIO_state(HIGH);
			display.display_Text("WORKING!\nC++!\nVERSION!!!!!!");
			wait = false;
        }
        vTaskDelay(10);
    }
}
