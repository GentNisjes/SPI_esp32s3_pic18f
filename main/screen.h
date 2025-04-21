#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <stddef.h>

// Define the struct used to pass data to the OLED task
typedef struct
{
    uint8_t *tx_data;
    uint8_t *rx_data;
    size_t length;
} screen_task_params_t;

// Function prototypes
void i2c_master_init(void);
void oled_task(void *pvParameters);

#endif // SCREEN_H
