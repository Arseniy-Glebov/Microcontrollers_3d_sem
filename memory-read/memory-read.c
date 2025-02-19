#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>

void read_uart_string(char *buffer, size_t max_length) {
    size_t index = 0;
    while (index < max_length - 1) {
        char ch = getchar();
        if (ch == '\r' || ch == '\n') {
            buffer[index] = '\0';
            return;
        }
        buffer[index++] = ch;
    }
    buffer[max_length - 1] = '\0';
}

int main()
{
    stdio_init_all();
    
    char command[32];
    char* endptr;
    uint32_t addr;

    while (true) {
        printf("Waiting for commands\n");
        
        read_uart_string(command, 32);
        
        addr = strtol(command, &endptr, 16);

        if (addr >= 0x10000000 && addr < 0x10200000) {
            printf("Address 0x%08lX is in Flash memory range.\n", addr);
            uint32_t *ptr = (uint32_t *)addr;
            uint32_t value = *ptr;
            printf("Memory value at 0x%08lX: 0x%08X\n", addr, value);
        } else if(addr >= 0x20000000 && addr < 0x20040000){
            printf("Address 0x%08lX is in SRAM memory range.\n", addr);
            uint32_t *ptr = (uint32_t *)addr;  
            uint32_t value = *ptr;  
            printf("Memory value at 0x%08lX: 0x%08X\n", addr, value);
        } else {
            printf("Address 0x%08lX is out of range.\n", addr);
        } 
}
}
