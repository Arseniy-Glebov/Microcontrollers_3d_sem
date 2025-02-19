#include <stdio.h>
#include "pico/stdlib.h"
int test = 890324;
int* test_pointer = &test; 

int main() {
    stdio_init_all();
    while (true)
    {
        sleep_ms(500);
        printf(test_pointer);
    }
}
