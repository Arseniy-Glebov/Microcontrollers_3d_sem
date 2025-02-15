#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"

#define PICO_DEFAULT_LED_PIN 25

int main()
{
    stdio_init_all();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while (true) {
        printf("Waiting for commands\n");
        char cur_sym = getchar(); 
        char command[50] = "";
        int counter = 0;
        while (cur_sym != '`')
        {
            command[counter] = cur_sym;
            cur_sym = getchar();
            counter++;
        }
        printf(command);
        printf("\n");
        int time = (int)command;
        
        /*
        time += 5;
        time *= 10;
        printf(time);
        printf("\n");
        
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        sleep_ms(time);
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        */
    }
}
