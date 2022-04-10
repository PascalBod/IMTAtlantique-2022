/**
 * This sample application simulates the reception of bytes on a serial link with
 * an Interrupt Service Routine.
 *
 * The reception ISR is simulated by a timer handler. At each activation of the
 * handler, a new byte is provided.
 *
 * The byte reception event is signaled to the background task by a flag. When the
 * background task sees that the flag is set, it reads the received byte, and
 * processes it. Time required by processing is simulated by a random wait period.
 *
 * A new byte is received every REC_PERIOD ms. Processing time is between
 * MIN_PROC_TIME ms and MAX_PROC_TIME ms.
 *
 * In order to be able to display log messages without influencing execution, time
 * periods are in the order of 1 second, instead of ms or µs as it would be for
 * a real application.
 */

#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

// Byte reception period, in ms.
#define REC_PERIOD 1000

// Lowest value of byte processing time, in ms.
#define MIN_PROC_TIME 300
// Highest value of byte processing time, in ms.
#define MAX_PROC_TIME 1200

// Wait period between two tests of rec flag, in ms.
#define WAIT_TIME 4

// For log messages.
static const char TAG[] = "MN";

// Received byte. The variable is used to exchange data between the
// timer handler and the background task.
static uint8_t rec_byte;
// Reception event flag.
static bool rec_flag;

// Timer handler, simulating the reception of a byte. Byte values
// are in sequence: 0, 1, 2 ... 255, 0, 1, 2 ...
static void timer_handler(TimerHandle_t timer)
{
	// Wrap around: after 255, rec_byte will be 0.
	rec_byte++;
	rec_flag = true;
}

void app_main(void)
{
	// Required variables for creating a timer.
	TimerHandle_t timer;
	uint8_t timer_id = 0;

	// For log purpose.
	uint8_t byte_before;

	// Create the timer used to simulate periodic reception of a byte.
	// In a real application, we should test that the timer is
	// successfully created.
	timer = xTimerCreate("SIMU_TIMER",
			pdMS_TO_TICKS(REC_PERIOD),
			pdTRUE,  // uxAutoReload.
			&timer_id,
			timer_handler);

	// Initialize global variables.
    rec_byte = 0;
    rec_flag = false;

    // Initialize random generator.
    srand(time(NULL));

    // Start byte reception simulation.
    // In a real application, we should test the return status.
    xTimerStart(timer, 0);

    // Time period variables used by the background task loop.
    int proc_time;
    TickType_t tick_proc_time;

    // Background task loop.
    while (true)
    {
    	if (rec_flag)
    	{
    		// A byte has been received. Reset reception event.
    		rec_flag = false;
    		// Remember byte value before processing.
    		byte_before = rec_byte;
    		// Process received byte: simulate processing time by waiting.
    		proc_time = MIN_PROC_TIME + (rand() % (MAX_PROC_TIME - MIN_PROC_TIME));
    		tick_proc_time = pdMS_TO_TICKS(proc_time);
    		vTaskDelay(tick_proc_time);
    		if (rec_byte == byte_before)
    		{
        		ESP_LOGI(TAG, "Before processing: %u - after: %u", byte_before, rec_byte);
    		}
    		else
    		{
    			ESP_LOGE(TAG, "Before processing: %u - after: %u", byte_before, rec_byte);
    		}
    	}
    	// Let the task watchdog be happy.
    	vTaskDelay(pdMS_TO_TICKS(WAIT_TIME));
    }

}
