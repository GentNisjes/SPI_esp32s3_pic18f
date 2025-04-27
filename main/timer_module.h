/*
    Filename: timer_module.h
    Description: This code provides functions to create and delete timer tasks using ESP-IDF's esp_timer API.
    Author: Lukas Varhol
    Date: 2023-10-01
 */

#ifndef TIMER_MODULE_H
#define TIMER_MODULE_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include <esp_timer.h>

esp_timer_handle_t create_timer_task(void *params, void callback(void *params), int interval_us);

void delete_timer_task(esp_timer_handle_t timer_handler);
esp_timer_handle_t create_oneshot_timer_task(void *params, void (*callback)(void *params));

void start_oneshot_timer(esp_timer_handle_t timer_handler, int delay_us);
#endif // TIMER_MODULE_H