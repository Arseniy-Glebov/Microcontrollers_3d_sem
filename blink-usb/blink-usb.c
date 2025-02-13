#include <stdio.h>
#include "pico/stdlib.h"

#define PICO_DEFAULT_LED_PIN 25

int main()
{
    stdio_init_all();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while (true) {
        char marker = getchar();
        printf("session\n");
        // printf(marker);
        // printf('\n');
        if (marker == '1')
        {
            printf("on\n");
            gpio_put(PICO_DEFAULT_LED_PIN, true);
        }else if (marker == '0')
        {
            printf("off\n");
            gpio_put(PICO_DEFAULT_LED_PIN, false);
        }
    }
}
