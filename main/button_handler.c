#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <stdio.h>
#include "esp_timer.h"

#define BUTTON_RIGHT_DOWN 12


typedef struct {
    gpio_num_t pin; // The GPIO pin the button is connected to.
    int state;      // The current state of the button (0 = not pressed, 1 = pressed).

} button_t;

button_t buttons[] = {
    {BUTTON_RIGHT_DOWN, 0}
    // Add other buttons here
};


const int NUM_BUTTONS = sizeof(buttons) / sizeof(button_t);
// --- End of Configuration ---

// Make sure you call this before you try to read the buttons
static void initialize_buttons() {

    for (int i = 0; i < NUM_BUTTONS; i++) { 
        button_t *button = &buttons[i];
        gpio_config_t io_conf;
        io_conf.intr_type = GPIO_INTR_DISABLE; // why do i have to do this?
        io_conf.mode = GPIO_MODE_INPUT;   
        io_conf.pin_bit_mask = (1ULL << button->pin);
        io_conf.pull_down_en = 0;            
        io_conf.pull_up_en = 1;                
        gpio_config(&io_conf);
    }
}


void button_poll_task(void *pvParameter) {
    while (1) {
        for (int i = 0; i < NUM_BUTTONS; i++) {
            buttons[i].state = !gpio_get_level(buttons[i].pin);
        }


        printf("Button states: ");
        for (int i = 0; i < NUM_BUTTONS; i++) {
            printf("GPIO %d: %s | ", buttons[i].pin, buttons[i].state ? "PRESSED" : "Released");
        }
        printf("\n");

        vTaskDelay(8 / portTICK_PERIOD_MS); // 1000ms / 125hz = 8ms
    }
}

// void app_main(void) {
//     // Create a task that will continuously read the button states.
//     // This runs the read_buttons_task on a separate thread.
//     xTaskCreate(read_buttons_task, "read_buttons_task", 2048, NULL, 10, NULL);
// }
