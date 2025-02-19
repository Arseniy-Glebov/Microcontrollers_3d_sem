#include <stdio.h>
#include "pico/stdlib.h"
#include <math.h>

#define PICO_DEFAULT_LED_PIN 25

void read_uart_string(char *buffer, size_t max_length) {
    size_t index = 0;
    while (index < max_length - 1) {
        char ch = getchar();  // Читаем символ
        if (ch == '\r' || ch == '\n') {  // Конец строки (Enter)
            buffer[index] = '\0';  // Завершаем строку
            return;
        }
        buffer[index++] = ch;  // Добавляем в буфер
    }
    buffer[max_length - 1] = '\0';  // Защита от переполнения
}

int main()
{
    stdio_init_all();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    char command[32];
    char* endptr;

    while (true) {
        printf("Waiting for commands\n");
        
        read_uart_string(command, 32);
        printf("Received: [%s]\n", command);
        
        int time = strtol(command, &endptr, 10);
        
        time *= 1000;
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        sleep_ms(time);
        gpio_put(PICO_DEFAULT_LED_PIN, false);
    }
}
