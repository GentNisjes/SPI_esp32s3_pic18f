// #ifndef SPI_H
// #define SPI_H

// #include <stdint.h>
// #include <stddef.h>
// #include "driver/spi_master.h"

// // Exposed buffer size if needed globally
// // #define SPI_BUFFER_SIZE 4

// // Task parameters struct
// typedef struct
// {
//     uint8_t *tx_data;
//     uint8_t *rx_data;
//     size_t length;
// } spi_task_params_t;

// // extern SemaphoreHandle_t spi_done_semaphore;

// // Function declarations
// void spi_master_init(void);
// void spi_task(void *params);

// #endif // SPI_H

#ifndef SPI_COMM_H
#define SPI_COMM_H

#include "driver/spi_master.h"

#define SPI_BUFFER_SIZE 10

typedef struct
{
    uint8_t tx_data[SPI_BUFFER_SIZE];
    bool expect_response;
} spi_packet_t;

// the SPI queue handle (defined in spi_comm.c)
extern QueueHandle_t spi_queue;

void spi_master_init(void);
void spi_task_start(void);
bool spi_send(const uint8_t *data, bool expect_response);

#endif
