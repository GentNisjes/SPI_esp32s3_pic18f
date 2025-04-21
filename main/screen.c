#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "ssd1306.h"
#include "main.h"

#define I2C_MASTER_NUM I2C_NUM_0
#define I2C_MASTER_SDA_IO 41
#define I2C_MASTER_SCL_IO 40
#define I2C_MASTER_FREQ_HZ 100000
// #define BUFFER_SIZE 4

typedef struct
{
    uint8_t *tx_data;
    uint8_t *rx_data;
    size_t length;
} screen_task_params_t;

// ===================== I2C CONFIG FUNCTION =====================
void i2c_master_init()
{
    i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &i2c_conf));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_MASTER_NUM, I2C_MODE_MASTER, 0, 0, 0));
}

// ===================== OLED SCREEN TASK =====================
void oled_task(void *pvParameters)
{
    screen_task_params_t *params = (screen_task_params_t *)pvParameters;

    i2c_master_init();

    ssd1306_handle_t oled = ssd1306_create(I2C_MASTER_NUM, SSD1306_I2C_ADDRESS);
    if (oled == NULL)
    {
        printf("Failed to create SSD1306 handle\n");
        vTaskDelete(NULL);
    }

    if (ssd1306_init(oled) != ESP_OK)
    {
        printf("SSD1306 init failed\n");
        vTaskDelete(NULL);
    }

    char buffer[32];

    while (1)
    {
        ssd1306_clear_screen(oled, 0x00);

        snprintf(buffer, sizeof(buffer), "TX:");
        ssd1306_draw_string(oled, 0, 0, (const uint8_t *)buffer, 16, 1);

        for (int i = 0; i < params->length; i++)
        {
            snprintf(buffer, sizeof(buffer), "0x%02X", params->tx_data[i]);
            ssd1306_draw_string(oled, i * 5, 8, (const uint8_t *)buffer, 8, 1);
        }

        snprintf(buffer, sizeof(buffer), "RX:");
        ssd1306_draw_string(oled, 0, 3, (const uint8_t *)buffer, 16, 1);

        for (int i = 0; i < params->length; i++)
        {
            snprintf(buffer, sizeof(buffer), "0x%02X", params->rx_data[i]);
            ssd1306_draw_string(oled, i * 5, 4, (const uint8_t *)buffer, 8, 1);
        }

        ssd1306_refresh_gram(oled);
        vTaskDelay(pdMS_TO_TICKS(500));
    }

    ssd1306_delete(oled);
    vTaskDelete(NULL);
}
