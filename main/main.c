
// #include "spi_master.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/semphr.h"
// #include "esp_log.h"
// #include "esp_system.h"
// #include "esp_err.h"
// #include "ssd1306.h"
// #include "screen.h"

// #define BUFFER_SIZE 4

// // SemaphoreHandle_t data_mutex;

// void app_main(void)
// {
//     // data_mutex = xSemaphoreCreateMutex();

//     // spi_comm_init();
//     // sensors_init();
//     // display_init();

//     // xTaskCreate(spi_task, "spi_task", 4096, NULL, 5, NULL);
//     // xTaskCreate(sensor_task, "sensor_task", 4096, NULL, 5, NULL);
//     // xTaskCreate(display_task, "display_task", 4096, NULL, 5, NULL);

//     spi_master_init();

//     static uint8_t tx_buf[BUFFER_SIZE] = {0xA0, 0x01, 0x02, 0x03};
//     static uint8_t rx_buf[BUFFER_SIZE] = {0};

//     static spi_task_params_t spi_params = {
//         .tx_data = tx_buf,
//         .rx_data = rx_buf,
//         .length = BUFFER_SIZE};

//     xTaskCreate(spi_task, "spi_task", 4096, &spi_params, 5, NULL);

//     //     if (xSemaphoreTake(spi_done_semaphore, pdMS_TO_TICKS(500)) == pdTRUE)
//     //     {
//     //         printf("Main: SPI transfer complete\n");

//     //         // static screen_task_params_t screen_params = {
//     //         //     .tx_data = tx_buf,
//     //         //     .rx_data = rx_buf,
//     //         //     .length = 4};

//     //         // xTaskCreate(oled_task, "screen_task", 4096, &screen_params, 4, NULL);
//     //     }
//     //     else
//     //     {
//     //         printf("SPI task timed out!\n");
//     //     }
// }

// #include <stdio.h>
// #include "driver/spi_master.h"
// #include "driver/gpio.h"
// #include "esp_err.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"

// #define SPI_MOSI 18 // Connected to SDI pin of PIC18F (RC5)
// #define SPI_MISO 19 // Connected to SDO pin of PIC18F (RC6)
// #define SPI_SCLK 20 // Connected to SCK pin of PIC18F (RC4)
// #define SPI_CS 48   // Connected to SS pin of PIC18F (RA6)

// #define BUFFER_SIZE 10 // Example buffer size

// spi_device_handle_t spi;

// void spi_master_init()
// {
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

// void app_main()
// {
//     // Initialize SPI master
//     spi_master_init();
//     printf("SPI Master initialized. Starting transactions...\n");

//     // Create data buffers for transmitting and receiving
//     uint8_t tx_data[BUFFER_SIZE] = {0x09, 0x00, 0x01, 0x02}; // 0x09, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
//     uint8_t rx_data[BUFFER_SIZE];                            // Buffer to store received data

//     // Initialize the tx_data buffer with some values
//     // for (int i = 0; i < BUFFER_SIZE; i++)
//     // {
//     //     tx_data[i] = i; // Just an example, filling with 0, 1, 2, ...
//     // }

//     // Wait for a moment to ensure the slave is ready
//     vTaskDelay(pdMS_TO_TICKS(1000));

//     // // Prepare transaction
//     // spi_transaction_t trans = {
//     //     .length = BUFFER_SIZE * 8, // Length in bits (BUFFER_SIZE bytes)
//     //     .tx_buffer = tx_data,
//     //     .rx_buffer = rx_data};

//     // // printf("Setting SS HIGH\n");
//     // // gpio_reset_pin(SPI_CS);
//     // // gpio_set_direction(SPI_CS, GPIO_MODE_OUTPUT);
//     // // gpio_set_level(SPI_CS, 0);
//     // // printf("SS pin state after setting HIGH: %d\n", gpio_get_level(SPI_CS));

//     // esp_err_t ret = spi_device_transmit(spi, &trans);

//     // // printf("Setting SS LOW\n");
//     // // gpio_set_level(SPI_CS, 1);
//     // // printf("SS pin state after setting LOW: %d\n", gpio_get_level(SPI_CS));

//     // if (ret == ESP_OK)
//     // {
//     //     printf("SPI Exchange: Sent %d bytes, Received %d bytes\n", BUFFER_SIZE, BUFFER_SIZE);
//     //     printf("Send Data: { ");
//     //     for (int i = 0; i < BUFFER_SIZE; i++)
//     //     {
//     //         printf("0x%02X%s", tx_data[i], (i < BUFFER_SIZE - 1) ? ", " : " ");
//     //     }
//     //     printf("}\n");
//     //     printf("Received Data: { ");
//     //     for (int i = 0; i < BUFFER_SIZE; i++)
//     //     {
//     //         printf("0x%02X%s", rx_data[i], (i < BUFFER_SIZE - 1) ? ", " : " ");
//     //     }
//     //     printf("}\n");
//     // }
//     // else
//     // {
//     //     printf("SPI transaction failed: %d\n", ret);
//     // }

//     while (1)
//     {
//         // Prepare transaction
//         spi_transaction_t trans = {
//             .length = BUFFER_SIZE * 8, // Length in bits (BUFFER_SIZE bytes)
//             .tx_buffer = tx_data,
//             .rx_buffer = rx_data};

//         // printf("Setting SS HIGH\n");
//         // // gpio_reset_pin(SPI_CS);
//         // // gpio_set_direction(SPI_CS, GPIO_MODE_OUTPUT);
//         // gpio_set_level(SPI_CS, 1);
//         // printf("SS pin state after setting HIGH: %d\n", gpio_get_level(SPI_CS));

//         esp_err_t ret = spi_device_transmit(spi, &trans);

//         // printf("Setting SS LOW\n");
//         // gpio_set_level(SPI_CS, 0);
//         // printf("SS pin state after setting LOW: %d\n", gpio_get_level(SPI_CS));

//         if (ret == ESP_OK)
//         {
//             printf("SPI Exchange: Sent %d bytes, Received %d bytes\n", BUFFER_SIZE, BUFFER_SIZE);
//             printf("Send Data: { ");
//             for (int i = 0; i < BUFFER_SIZE; i++)
//             {
//                 printf("0x%02X%s", tx_data[i], (i < BUFFER_SIZE - 1) ? ", " : " ");
//             }
//             printf("}\n");
//             printf("Received Data: { ");
//             for (int i = 0; i < BUFFER_SIZE; i++)
//             {
//                 printf("0x%02X%s", rx_data[i], (i < BUFFER_SIZE - 1) ? ", " : " ");
//             }
//             printf("}\n");
//         }
//         else
//         {
//             printf("SPI transaction failed: %d\n", ret);
//         }

//         // Wait before next transaction
//         vTaskDelay(pdMS_TO_TICKS(1000)); // 1 second delay
//     }
// }

// #include <stdio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "spi_master.h"

// void app_main(void)
// {
//     spi_master_init();
//     spi_task_start();

//     // Sample packet
//     uint8_t data_to_send[SPI_BUFFER_SIZE] = {0xAA, 0xBB, 0x01, 0x02, 0x03, 0, 0, 0, 0, 0};

//     while (1)
//     {
//         bool success = spi_send(data_to_send, true);
//         if (!success)
//         {
//             printf("Failed to send SPI packet\n");
//         }
//         vTaskDelay(pdMS_TO_TICKS(2000));
//     }
// }

// __________________________________________________

// #include <stdio.h>
// #include <string.h>
// #include "freertos/FreeRTOS.h"
// #include "spi_master.h"
// #include "timer_module.h"

// // a static packet to send every 2 ms
// static uint8_t const periodic_data[SPI_BUFFER_SIZE] = {
//     0xA0, 0x01, 0x02, /* … fill to 10 bytes … */ 0, 0, 0, 0, 0, 0};
// static esp_timer_handle_t spi_timer;

// static void spi_timer_cb(void *arg)
// {
//     // Note: called in ESP timer task, must use FromISR API
//     spi_packet_t pkt;
//     memcpy(pkt.tx_data, periodic_data, SPI_BUFFER_SIZE);
//     pkt.expect_response = true;

//     BaseType_t hpw = pdFALSE;
//     xQueueSendFromISR(spi_queue, &pkt, &hpw);
//     portYIELD_FROM_ISR(hpw);
// }

// void app_main(void)
// {
//     // initialize SPI and start its consumer task
//     spi_master_init();
//     spi_task_start();

//     // set up a 2 ms periodic SPI callback
//     spi_timer = create_timer_task(NULL, spi_timer_cb, 2000000);
//     printf("SPI timer started\n");
// }

//______________________________________

// // main.c
// #include <stdio.h>
// #include <string.h>
// #include "freertos/FreeRTOS.h"
// #include "spi_master.h"
// #include "timer_module.h"

// static esp_timer_handle_t spi_timer;

// static void spi_timer_cb(void *arg)
// {
//     // Note: called in ESP timer task, must use FromISR API

//     // Create search data
//     SearchData search = {
//         .wallLeft = true,
//         .wallRight = false,
//         .wallUp = true,
//         .wallDown = false,
//         .direction = 1 // right
//     };

//     // Send it using the ISR-safe function
//     BaseType_t hpw = pdFALSE;
//     spi_send_search_data_from_isr(&search, &hpw);
//     portYIELD_FROM_ISR(hpw);
// }

// // Alternative: If you want to keep sending raw data periodically
// static void raw_spi_timer_cb(void *arg)
// {
//     static uint8_t const periodic_data[SPI_BUFFER_SIZE] = {
//         0xA0, 0x01, 0x02, /* ... fill to 32 bytes ... */ 0, 0, 0, 0, 0, 0};

//     spi_packet_t pkt;
//     memcpy(pkt.tx_data, periodic_data, SPI_BUFFER_SIZE);
//     pkt.expect_response = true;

//     BaseType_t hpw = pdFALSE;
//     xQueueSendFromISR(spi_queue, &pkt, &hpw);
//     portYIELD_FROM_ISR(hpw);
// }

// void app_main(void)
// {
//     // Initialize SPI and start its consumer task
//     spi_master_init();
//     spi_task_start();

//     // Set up a 2 ms periodic SPI callback
//     spi_timer = create_timer_task(NULL, spi_timer_cb, 15000000);
//     printf("SPI timer started\n");

//     // Example of regular (non-ISR) sending
//     // SolveData solve = {
//     //     .x = 10,
//     //     .y = 15,
//     //     .direction = 2, // down
//     //     .hasBarcode = true,
//     //     .barcode = 0xAA};

//     // // Regular sending - not from ISR
//     // spi_send_solve_data(&solve);
// }

// _____________________________________________________

// // main.c - Dynamic flexible approach
// #include <stdio.h>
// #include <string.h>
// #include "freertos/FreeRTOS.h"
// #include "spi_master.h"
// #include "timer_module.h"

// // Context structure to hold both data and timer handle
// typedef struct
// {
//     SearchData data;
//     esp_timer_handle_t timer_handle;
// } TimerCallbackContext;

// // Global context (could also be dynamically allocated)
// static TimerCallbackContext timer_context;

// // Callback that receives the context as argument
// static void spi_oneshot_cb_dynamic(void *arg)
// {
//     TimerCallbackContext *ctx = (TimerCallbackContext *)arg;

//     // Send the search data using the ISR-safe function
//     BaseType_t hpw = pdFALSE;
//     spi_send_search_data_from_isr(&ctx->data, &hpw);
//     portYIELD_FROM_ISR(hpw);
// }

// // Function to trigger SPI send when path finding completes
// void path_finding_complete(SearchData *result)
// {
//     // Copy the result to our context
//     memcpy(&timer_context.data, result, sizeof(SearchData));

//     // Start the one-shot timer
//     start_oneshot_timer(timer_context.timer_handle, 0);
// }

// // Example path finding task
// void path_finding_task(void *params)
// {
//     // while (1)
//     //{
//     // Simulate path finding calculation
//     vTaskDelay(pdMS_TO_TICKS(1000));

//     // When walls are detected and next cell is calculated
//     SearchData search_result = {
//         .wallLeft = false,
//         .wallRight = true,
//         .wallUp = false,
//         .wallDown = true,
//         .direction = 2 // down
//     };

//     // Trigger the one-shot timer to send data
//     path_finding_complete(&search_result);
//     //}
//     // vTaskDelay(pdMS_TO_TICKS(1000000)); // timer of

//     // Add this line to properly delete the task when it's done
//     vTaskDelete(NULL);
// }

// void app_main(void)
// {
//     // Initialize SPI and start its consumer task
//     spi_master_init();
//     spi_task_start();

//     // Create the one-shot timer with context passed as argument
//     timer_context.timer_handle = create_oneshot_timer_task(&timer_context, spi_oneshot_cb_dynamic);

//     // Create the path finding task
//     xTaskCreate(path_finding_task, "path_finding", 4096, NULL, 5, NULL);

//     printf("SPI system started with dynamic data passing\n");
// }

//________________________________________________________

// // main.c - Dynamic flexible approach
// #include <stdio.h>
// #include <string.h>
// #include "freertos/FreeRTOS.h"
// #include "spi_master.h"
// #include "timer_module.h"

// // Context structure to hold both data and timer handle
// typedef struct
// {
//     SearchData data;
//     esp_timer_handle_t timer_handle;
// } TimerCallbackContext;

// // Global context (could also be dynamically allocated)
// static TimerCallbackContext timer_context;

// // Callback that receives the context as argument
// static void spi_oneshot_cb_dynamic(void *arg)
// {
//     TimerCallbackContext *ctx = (TimerCallbackContext *)arg;

//     // Send the search data using the ISR-safe function
//     BaseType_t hpw = pdFALSE;
//     spi_send_search_data_from_isr(&ctx->data, &hpw);
//     portYIELD_FROM_ISR(hpw);
// }

// // Function to trigger SPI send when path finding completes
// void path_finding_complete(SearchData *result)
// {
//     // Copy the result to our context
//     memcpy(&timer_context.data, result, sizeof(SearchData));

//     // Start the one-shot timer
//     start_oneshot_timer(timer_context.timer_handle, 0);
// }

// // Example path finding task
// void path_finding_task(void *params)
// {
//     while (1)
//     {
//         // Simulate path finding calculation
//         vTaskDelay(pdMS_TO_TICKS(1000));

//         // When walls are detected and next cell is calculated
//         SearchData search_result = {
//             .wallLeft = false,
//             .wallRight = true,
//             .wallUp = false,
//             .wallDown = true,
//             .direction = 2 // down
//         };

//         // Trigger the one-shot timer to send data
//         path_finding_complete(&search_result);
//     }
// }

// void app_main(void)
// {
//     // Initialize SPI and start its consumer task
//     spi_master_init();
//     spi_task_start();

//     // Create the one-shot timer with context passed as argument
//     timer_context.timer_handle = create_oneshot_timer_task(&timer_context, spi_oneshot_cb_dynamic);

//     // Create the path finding task
//     xTaskCreate(path_finding_task, "path_finding", 4096, NULL, 5, NULL);

//     printf("SPI system started with dynamic data passing\n");
// }

//_____________________________________________________
// main.c - Direct approach without timers
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "spi_master.h"

// Function to send search data directly using existing SPI functions
void send_search_data(const SearchData *data)
{
    // Create a buffer for SPI communication
    uint8_t buffer[SPI_BUFFER_SIZE];

    // Clear the buffer
    memset(buffer, 0, SPI_BUFFER_SIZE);

    // Pack the wall data into the first byte
    buffer[0] = 0;
    if (data->wallLeft)
        buffer[0] |= 0x01;
    if (data->wallRight)
        buffer[0] |= 0x02;
    if (data->wallUp)
        buffer[0] |= 0x04;
    if (data->wallDown)
        buffer[0] |= 0x08;

    // Set the direction in the second byte
    buffer[1] = data->direction;

    // Send the data directly using the existing SPI function
    bool success = spi_send(buffer, true);
    if (!success)
    {
        printf("Failed to send SPI packet\n");
    }
}

// Function to trigger SPI send when path finding completes
void path_finding_complete(SearchData *result)
{
    // Directly send the data without using a timer
    send_search_data(result);
}

// Example path finding task
void path_finding_task(void *params)
{
    while (1)
    {
        // Simulate path finding calculation
        vTaskDelay(pdMS_TO_TICKS(1000));

        // When walls are detected and next cell is calculated
        SearchData search_result = {
            .wallLeft = false,
            .wallRight = true,
            .wallUp = false,
            .wallDown = true,
            .direction = 2 // down
        };

        // Directly call the function to send data - no timer needed
        path_finding_complete(&search_result);
    }
}

void app_main(void)
{
    // Initialize SPI and start its consumer task
    spi_master_init();
    spi_task_start();

    // Create the path finding task
    xTaskCreate(path_finding_task, "path_finding", 4096, NULL, 5, NULL);

    printf("SPI system started with direct send approach\n");
}