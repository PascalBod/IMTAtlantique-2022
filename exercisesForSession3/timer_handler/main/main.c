/**
 * This sample application shows how to use a FreeRTOS timer.
 *
 * Documentation: https://www.freertos.org/RTOS-software-timer.html
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

// Timer handler, called on timer expiration. In FreeRTOS,
// a timer handler is not called from an interrupt context.
static void timer_handler(TimerHandle_t timer)
{
	ESP_DRAM_LOGI(TAG, "Timer handler");
}

void app_main(void)
{
	// Required variables for creating a timer.
	TimerHandle_t timer;
	uint8_t timer_id = 0;

	// Create the timer.
	// In a real application, we should test that the timer is
	// successfully created.
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
