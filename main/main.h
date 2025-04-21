#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

#define BUFFER_SIZE 10

void spi_task(void *params);
void oled_task(void *params);

#endif // MAIN_H
