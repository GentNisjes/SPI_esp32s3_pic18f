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

#define SPI_BUFFER_SIZE 32

typedef struct
{
    uint8_t tx_data[SPI_BUFFER_SIZE];
    bool expect_response;
} spi_packet_t;

typedef struct
{
    bool wallLeft;
    bool wallRight;
    bool wallUp;
    bool wallDown;
    uint8_t direction; // 0=up, 1=right, 2=down, 3=left
} SearchData;

typedef struct
{
    uint8_t x;
    uint8_t y;
    uint8_t direction;
    bool hasBarcode;
    uint8_t barcode;
} SolveData;

// Message types
typedef enum
{
    NRF_TYPE_SEARCH = 0,
    NRF_TYPE_SOLVE = 1
} nrf_msg_type_t;

// the SPI queue handle (defined in spi_comm.c)
extern QueueHandle_t spi_queue;

void spi_master_init(void);
void spi_task_start(void);
bool spi_send(const uint8_t *data, bool expect_response);
bool spi_send_json(const char *json_str);

bool spi_send_from_isr(const uint8_t *data, bool expect_response, BaseType_t *pxHigherPriorityTaskWoken);
bool spi_send_search_data_from_isr(const SearchData *data, BaseType_t *pxHigherPriorityTaskWoken);
bool spi_send_solve_data_from_isr(const SolveData *data, BaseType_t *pxHigherPriorityTaskWoken);

bool spi_send_search_data(const SearchData *data);
bool spi_send_solve_data(const SolveData *data);

#endif
