/**
 * Copyright 2022 Pascal Bodin
 */

#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

// Timer period, in ms.
#define TIMER_PERIOD 1000

// For log messages.
static const char TAG[] = "MN";

TimerHandle_t timer;

// Next timer period.
uint32_t next_period = TIMER_PERIOD;

// Timer handler, called on timer expiration. In FreeRTOS,
// a timer handler is not called from an interrupt context.
static void timer_handler(TimerHandle_t timer)
{
	ESP_LOGI(TAG, "Timer handler");
	// Double the timer period.
	next_period *= 2;
	// Change the timer period.
	xTimerChangePeriod(timer, pdMS_TO_TICKS(next_period), 0);
	ESP_LOGI(TAG, "Next period: %d", next_period);
}

void app_main(void)
{
	// Create the timer.
	// In a real application, we should test that the timer is
	// successfully created.
	uint8_t timer_id = 0;
	timer = xTimerCreate("OurTimer",
			pdMS_TO_TICKS(TIMER_PERIOD),
			pdTRUE,  // uxAutoReload.
			&timer_id,
			timer_handler);

	// Start timer.
    xTimerStart(timer, 0);

    // We can exit: the task is cleaned up and the system will
    // continue running with other RTOS tasks scheduled normally.
    // They include the timer service task.
}
