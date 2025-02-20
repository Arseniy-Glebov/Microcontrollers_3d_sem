#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include <time.h>

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

    printf("ADC Example, measuring GPIO26\n");

    adc_init();

    adc_gpio_init(26);
    adc_select_input(0);

    gpio_init(10);
    gpio_set_dir(10, GPIO_OUT);
    
    const float conversion_factor = 3.3f / (1 << 12);
    clock_t time_diff;
    uint16_t result;
    char command[32];
    while (true){
        read_uart_string(command, 32);
        printf("%s\n", command);
        if (strcmp(command, "START") == 0){
            clock_t start = clock();
            gpio_put(10, true);
            do {
                read_uart_string(command, 32);
                result = adc_read();
                time_diff = (clock() - start) * 1000 / CLOCKS_PER_SEC;;
                printf("Time: %d, Raw value: 0x%03x, voltage: %f V\n", time_diff, result, result * conversion_factor);
                sleep_ms(50);
            } while(strcmp(command, "CAP_LOW") != 0);
            gpio_put(10, false);
            do {
                read_uart_string(command, 32);
                result = adc_read();
                time_diff = (clock() - start) * 1000 / CLOCKS_PER_SEC;;
                printf("Time: %d, Raw value: 0x%03x, voltage: %f V\n", time_diff, result, result * conversion_factor);
                sleep_ms(50);
            } while(strcmp(command, "STOP") != 0);
        }
    }
}
