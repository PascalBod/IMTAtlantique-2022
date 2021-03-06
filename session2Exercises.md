# Session 2 exercises

## Download the exercises

In the Linux VM, open a terminal (**Main menu > Terminal**, in the task bar). In this terminal, create a directory where you will download a copy of the ESP-IDF projects used by the exercises:

```shell
$ # Be sure to be in your home directory.
$ cd ~
$ # You can create a directory named Dev, for instance.
$ mkdir Dev
$ cd Dev
$ # Download the exercises.
$ git clone git@github.com:PascalBod/IMTAtlantique-2022.git
```

Using the above commands, exercises for session 3 are downloaded in `~/Dev/IMTAtlantique-2022/session2Exercises`.

## Get acquainted with timers

This exercise shows how to create and use a periodic timer. Its source code is in `~/Dev/IMTAtlantique-2022/session2Exercises/timer_handler`.

Import the associated project into Eclipse, with **File > Import... > Espressif > Existing IDF Project**:
* In the **Import** window, after having selected **Existing IDF Project**, click the **Next >** button
* In the **Import Project** window, click the **Browse...** button, select the `timer_handler` directory and click the **Open** button
* Click the **Finish** button

In the **Project Explorer** view, you now have the `timer_handler` project. Build it, flash the ESP32 board, and open an Eclipse terminal to display the application log messages.

Look at the source code. The example uses a [FreeRTOS timer](https://www.freertos.org/RTOS-software-timer.html). The timer handler function is called repeatedly, with the same period each time. 

Try to modify the application:
* change the timer period (easy!)
* try to modify the application so that the timer handler function is called after a different time period each time, for instance doubling the period after each time.

The FreeRTOS timer API is presented [here](https://www.freertos.org/FreeRTOS-Software-Timer-API-Functions.html).

## Background task and ISR

This exercise simulates the reception of bytes from a serial connection. A timer is used to simulate the periodic byte reception, the timer handler playing the role of the ISR. Its source code is in `~/Dev/IMTAtlantique-2022/session2Exercises/sim_serial`.

Import the project into Eclipse.

The background task processes each received byte. Usually, a real process would wait for several bytes (generated by a sensor for instance) and then apply some more or less complex processing (if the sensor is a camera, the processing could be an image classification, for instance).

In the code here, we simulate a more or less long processing by waiting for a random time period.

Run the application, and observe its behavior. How do you explain what happens?

## NMEA message decoder bugs

There is one critical issue in the [NMEA decoder FSA](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/7/60). Find which one and correct it

If the serial link is disconnected and reconnected, next complete NMEA message may be lost. Under which conditions? How to correct this?
