#include <stdio.h>
#include "pico/stdlib.h"
#include <math.h>

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
        int time = 0;
        while (cur_sym != '`')
        {
            command[counter] = cur_sym;
            cur_sym = getchar();
            time += (int)cur_sym * pow(10, counter);
            counter++;
        }
        
        //time *= 100;
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        sleep_ms(time);
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        
    }
}
