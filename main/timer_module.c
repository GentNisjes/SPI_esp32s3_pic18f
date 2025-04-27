/*
    Filename: timer_module.c
    Description: This code provides functions to create and delete timer tasks using ESP-IDF's esp_timer API.
    Author: Lukas Varhol
    Date: 2023-10-01
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include <esp_timer.h>

esp_timer_handle_t create_timer_task(void *params, void (*callback)(void *params), int interval_us)
{
    const esp_timer_create_args_t timer_args = {
        .callback = callback,
        .arg = params,
        .name = "timer_task"};

    esp_timer_handle_t timer_handler;
    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer_handler));
    ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handler, interval_us)); // 1ms interval

    return timer_handler;
};

void delete_timer_task(esp_timer_handle_t timer_handler)
{
    if (timer_handler)
    {
        ESP_ERROR_CHECK(esp_timer_stop(timer_handler));
        ESP_ERROR_CHECK(esp_timer_delete(timer_handler));
    }
}

// New function for one-shot timer
esp_timer_handle_t create_oneshot_timer_task(void *params, void (*callback)(void *params))
{
    const esp_timer_create_args_t timer_args = {
        .callback = callback,
        .arg = params,
        .name = "oneshot_timer_task"};

    esp_timer_handle_t timer_handler;
    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer_handler));

    return timer_handler;
}

// Start a one-shot timer with delay
void start_oneshot_timer(esp_timer_handle_t timer_handler, int delay_us)
{
    ESP_ERROR_CHECK(esp_timer_start_once(timer_handler, delay_us));
}