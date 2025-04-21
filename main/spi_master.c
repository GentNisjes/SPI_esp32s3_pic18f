// #include <stdio.h>
// #include "driver/spi_master.h"
// #include "driver/gpio.h"
// #include "esp_err.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "spi_master.h"
// #include "main.h"
// #include <freertos/semphr.h>

// // Declare the semaphore
// // SemaphoreHandle_t spi_done_semaphore = NULL;

// #define SPI_MOSI 18 // Connected to SDI pin of PIC18F (RC5)
// #define SPI_MISO 19 // Connected to SDO pin of PIC18F (RC6)
// #define SPI_SCLK 20 // Connected to SCK pin of PIC18F (RC4)
// #define SPI_CS 48   // Connected to SS pin of PIC18F (RA6)

// // #define BUFFER_SIZE 10 // Example buffer size

// spi_device_handle_t spi;

// void spi_master_init()
// {
//     // Initialize the semaphore
//     // spi_done_semaphore = xSemaphoreCreateBinary();
//     // if (spi_done_semaphore == NULL)
//     // {
//     //     printf("Failed to create semaphore\n");
//     //     return;
//     // }

//     // SPI bus configuration
//     spi_bus_config_t buscfg = {
//         .mosi_io_num = SPI_MOSI,
//         .miso_io_num = SPI_MISO,
//         .sclk_io_num = SPI_SCLK,
//         .quadwp_io_num = -1,
//         .quadhd_io_num = -1};

//     // SPI device configuration
//     spi_device_interface_config_t devcfg = {
//         .clock_speed_hz = 100000, // 1MHz SPI clock
//         .mode = 1,                // Mode 1: CPOL=0, CPHA=1
//         .spics_io_num = SPI_CS,
//         .queue_size = 1};

//     // Initialize SPI bus
//     esp_err_t ret = spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
//     if (ret != ESP_OK)
//     {
//         printf("Failed to initialize SPI bus: %d\n", ret);
//         return;
//     }

//     // Attach device to SPI bus
//     ret = spi_bus_add_device(SPI2_HOST, &devcfg, &spi);
//     if (ret != ESP_OK)
//     {
//         printf("Failed to add SPI device: %d\n", ret);
//         return;
//     }

//     printf("SPI master initialized successfully\n");
// }

// // void app_main()
// // {
// //     // Initialize SPI master
// //     spi_master_init();
// //     printf("SPI Master initialized. Starting transactions...\n");

// //     // Create data buffers for transmitting and receiving
// //     uint8_t tx_data[BUFFER_SIZE] = {0x09, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
// //     uint8_t rx_data[BUFFER_SIZE]; // Buffer to store received data

// //     // Wait for a moment to ensure the slave is ready
// //     vTaskDelay(pdMS_TO_TICKS(1000));

// //     // Prepare transaction
// //     spi_transaction_t trans = {
// //         .length = BUFFER_SIZE * 8, // Length in bits (BUFFER_SIZE bytes)
// //         .tx_buffer = tx_data,
// //         .rx_buffer = rx_data};

// //     esp_err_t ret = spi_device_transmit(spi, &trans);

// //     if (ret == ESP_OK)
// //     {
// //         printf("SPI Exchange: Sent %d bytes, Received %d bytes\n", BUFFER_SIZE, BUFFER_SIZE);
// //         printf("Send Data: { ");
// //         for (int i = 0; i < BUFFER_SIZE; i++)
// //         {
// //             printf("0x%02X%s", tx_data[i], (i < BUFFER_SIZE - 1) ? ", " : " ");
// //         }
// //         printf("}\n");
// //         printf("Received Data: { ");
// //         for (int i = 0; i < BUFFER_SIZE; i++)
// //         {
// //             printf("0x%02X%s", rx_data[i], (i < BUFFER_SIZE - 1) ? ", " : " ");
// //         }
// //         printf("}\n");
// //     }
// //     else
// //     {
// //         printf("SPI transaction failed: %d\n", ret);
// //     }
// // }

// esp_err_t spi_exchange(uint8_t *tx_data, uint8_t *rx_data, size_t len)
// {
//     spi_transaction_t trans = {
//         .length = len * 8, // bits
//         .tx_buffer = tx_data,
//         .rx_buffer = rx_data};

//     return spi_device_transmit(spi, &trans);
// }

// // When the function returns, FreeRTOS doesn’t know what to do, and it crashes with that "should not return" panic.
// // this can be fixed by using vTaskDelete(NULL) to delete the task after it has completed its work.
// // but deleting the task, can cause the receiving buffer to be freed before the data is read, which can lead to undefined behavior.
// // to fix this, we can use a mutex or semaphore to protect the buffer until the data is read.
// // or we can use a queue to send the data to another task that will handle it.

// void spi_task(void *pvParameters)
// {
//     spi_task_params_t *params = (spi_task_params_t *)pvParameters;

//     // vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for a moment to ensure
//     //  uint8_t tx_buf[BUFFER_SIZE];
//     //  uint8_t rx_buf[BUFFER_SIZE];

//     // esp_err_t ret = spi_exchange(params->tx_data, params->rx_data, params->length);

//     // if (ret == ESP_OK)
//     // {
//     //     printf("SPI Exchange: Sent %d bytes, Received %d bytes\n", BUFFER_SIZE, BUFFER_SIZE);
//     //     printf("Send Data: { ");
//     //     for (int i = 0; i < params->length; i++)
//     //     {
//     //         printf("0x%02X%s", params->tx_data[i], (i < params->length - 1) ? ", " : " ");
//     //     }
//     //     printf("}\n");
//     //     printf("Received Data: { ");
//     //     for (int i = 0; i < params->length; i++)
//     //     {
//     //         printf("0x%02X%s", params->rx_data[i], (i < params->length - 1) ? ", " : " ");
//     //     }
//     //     printf("}\n");
//     // }
//     // else
//     // {
//     //     printf("SPI transaction failed: %d\n", ret);
//     // }

//     // Notify that we're done
//     // xSemaphoreGive(spi_done_semaphore);

//     // vTaskDelete(NULL); // Delete the task after completion

//     while (1)
//     {
//         // Fill tx_buf with new data or wait for signal/queue...
//         esp_err_t ret = spi_exchange(params->tx_data, params->rx_data, params->length);
//         //  esp_err_t ret = spi_exchange(tx_buf, rx_buf, BUFFER_SIZE);

//         if (ret == ESP_OK)
//         {
//             printf("SPI Exchange: Sent %d bytes, Received %d bytes\n", BUFFER_SIZE, BUFFER_SIZE);
//             printf("Send Data: { ");
//             for (int i = 0; i < params->length; i++)
//             {
//                 printf("0x%02X%s", params->tx_data[i], (i < params->length - 1) ? ", " : " ");
//             }
//             printf("}\n");
//             printf("Received Data: { ");
//             for (int i = 0; i < params->length; i++)
//             {
//                 printf("0x%02X%s", params->rx_data[i], (i < params->length - 1) ? ", " : " ");
//             }
//             printf("}\n");
//         }
//         else
//         {
//             printf("SPI transaction failed: %d\n", ret);
//         }

//         vTaskDelay(pdMS_TO_TICKS(1000)); // Adjust frequency
//     }
// }

// #include <stdio.h>
// #include "driver/spi_master.h"
// #include "driver/gpio.h"
// #include "esp_err.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/semphr.h"

// #include "main.h"
// #include "spi_master.h"

// // Pin configuration
// #define SPI_MOSI 18
// #define SPI_MISO 19
// #define SPI_SCLK 20
// #define SPI_CS 48

// static spi_device_handle_t spi_handle;

// // === SPI Setup Functions === //

// void spi_master_bus_init(void)
// {
//     spi_bus_config_t buscfg = {
//         .mosi_io_num = SPI_MOSI,
//         .miso_io_num = SPI_MISO,
//         .sclk_io_num = SPI_SCLK,
//         .quadwp_io_num = -1,
//         .quadhd_io_num = -1,
//         .max_transfer_sz = BUFFER_SIZE};

//     esp_err_t ret = spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
//     if (ret != ESP_OK)
//     {
//         printf("Failed to initialize SPI bus: %s\n", esp_err_to_name(ret));
//     }
// }

// void spi_master_device_init(void)
// {
//     spi_device_interface_config_t devcfg = {
//         .clock_speed_hz = 100000, // 100 kHz
//         .mode = 1,                // CPOL=0, CPHA=1
//         .spics_io_num = SPI_CS,
//         .queue_size = 1};

//     esp_err_t ret = spi_bus_add_device(SPI2_HOST, &devcfg, &spi_handle);
//     if (ret != ESP_OK)
//     {
//         printf("Failed to add SPI device: %s\n", esp_err_to_name(ret));
//     }
// }

// void spi_master_init(void)
// {
//     spi_master_bus_init();
//     spi_master_device_init();
//     printf("SPI Master fully initialized.\n");
// }

// // === SPI Communication Function === //

// void spi_exchange_data(void)
// {
//     uint8_t tx_data[BUFFER_SIZE] = {0x09, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
//     uint8_t rx_data[BUFFER_SIZE] = {0};

//     spi_transaction_t trans = {
//         .length = BUFFER_SIZE * 8,
//         .tx_buffer = tx_data,
//         .rx_buffer = rx_data};

//     esp_err_t ret = spi_device_transmit(spi_handle, &trans);

//     if (ret == ESP_OK)
//     {
//         printf("SPI Exchange: Sent %d bytes, Received %d bytes\n", BUFFER_SIZE, BUFFER_SIZE);
//         printf("Sent Data: { ");
//         for (int i = 0; i < BUFFER_SIZE; i++)
//         {
//             printf("0x%02X%s", tx_data[i], (i < BUFFER_SIZE - 1) ? ", " : " ");
//         }
//         printf("}\nReceived Data: { ");
//         for (int i = 0; i < BUFFER_SIZE; i++)
//         {
//             printf("0x%02X%s", rx_data[i], (i < BUFFER_SIZE - 1) ? ", " : " ");
//         }
//         printf("}\n");
//     }
//     else
//     {
//         printf("SPI transaction failed: %s\n", esp_err_to_name(ret));
//     }
// }

// // === SPI Task === //

// void spi_task(void *pvParameters)
// {
//     while (1)
//     {
//         spi_exchange_data();
//         vTaskDelay(pdMS_TO_TICKS(1000)); // Delay between transactions
//     }
// }

#include <stdio.h>
#include <string.h>
#include "spi_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/spi_master.h"

#define SPI_MOSI 18
#define SPI_MISO 19
#define SPI_SCLK 20
#define SPI_CS 48

static spi_device_handle_t spi_handle;
QueueHandle_t spi_queue = NULL;

void spi_master_init(void)
{
    spi_bus_config_t buscfg = {
        .mosi_io_num = SPI_MOSI,
        .miso_io_num = SPI_MISO,
        .sclk_io_num = SPI_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1};

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 100000,
        .mode = 1,
        .spics_io_num = SPI_CS,
        .queue_size = 1};

    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &devcfg, &spi_handle));

    spi_queue = xQueueCreate(5, sizeof(spi_packet_t));
    printf("SPI Master initialized.\n");
}

// CONSUMER
// If pkt.expect_response is true, then rx_buffer is set to the address of our local array rx_data[].
// If pkt.expect_response is false, then rx_buffer is set to NULL.

// If you give the driver an rx_buffer, it will store each of those clocked‐in bits into that buffer.
// If you pass NULL, the driver will still toggle the clocks, but it won’t bother writing the incoming bits into memory.

static void spi_task(void *pvParams)
{
    spi_packet_t pkt;
    uint8_t rx_data[SPI_BUFFER_SIZE] = {0};

    while (1)
    {
        if (xQueueReceive(spi_queue, &pkt, portMAX_DELAY))
        {
            spi_transaction_t trans = {
                .length = SPI_BUFFER_SIZE * 8,
                .tx_buffer = pkt.tx_data,
                .rx_buffer = pkt.expect_response ? rx_data : NULL};

            esp_err_t ret = spi_device_transmit(spi_handle, &trans);
            if (ret == ESP_OK)
            {
                printf("SPI Sent: ");
                for (int i = 0; i < SPI_BUFFER_SIZE; i++)
                {
                    printf("0x%02X ", pkt.tx_data[i]);
                }
                printf("\n");

                if (pkt.expect_response)
                {
                    printf("SPI Received: ");
                    for (int i = 0; i < SPI_BUFFER_SIZE; i++)
                    {
                        printf("0x%02X ", rx_data[i]);
                    }
                    printf("\n");
                }
            }
            else
            {
                printf("SPI Tx failed: %s\n", esp_err_to_name(ret));
            }
        }
    }
}

void spi_task_start(void)
{
    xTaskCreate(spi_task, "spi_task", 4096, NULL, 5, NULL);
}

// PRODUCER
// This function is called to send data over SPI. It takes a pointer to the data to be sent and a boolean indicating whether a response is expected.
// It creates a spi_packet_t structure, copies the data into it, and sends it to the queue for processing by the spi_task.
bool spi_send(const uint8_t *data, bool expect_response)
{
    if (!spi_queue)
        return false;

    spi_packet_t pkt = {.expect_response = expect_response};
    memcpy(pkt.tx_data, data, SPI_BUFFER_SIZE);

    return xQueueSend(spi_queue, &pkt, pdMS_TO_TICKS(100)) == pdTRUE;
}
