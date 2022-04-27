# Solutions to session 2 exercises

## Modifying the timer period

The [FreeRTOS timer API](https://www.freertos.org/FreeRTOS-Software-Timer-API-Functions.html) provides a function named [`xTimerChangePeriod`](https://www.freertos.org/FreeRTOS-timers-xTimerChangePeriod.html).

To use it:
* move the timer declaration to the top most level (outside of `main`)
* in the timer handler, call `xTimerChangePeriod`

Resulting code: see [timer_handler_double project](https://github.com/PascalBod/IMTAtlantique-2022/tree/main/session2Solutions/timer_handler_double).

## Background task and ISR

From time to time, the next byte is provided by the interrupt routine while the background task is still processing the previous byte. So, the byte value is modified during the processing.

Simple modification: in the background task, make a copy of the received byte, and work on it. But if two successive bytes are received very rapidly, while the background task is busy, the first of them will be lost.

A [circular buffer](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/7/63) is a solution. Of course, the average processing speed must be a little bit more than the average byte reception speed. And the buffer must be large enough to absorb reception peaks.

## NMEA message decoder bugs

### Critical issue

When processing a message, its payload (the bytes between `$GP` and final `CR LF`) are stored into a reception buffer. This buffer has a given length. If more bytes than the buffer can store are received, we get a *buffer overflow*: received bytes are stored into the memory after the memory used by the buffer. This is a usual way to attack applications!

Solution: in `waitCR` state, check `msg_length` against reception buffer length. If it is greater, reset the automaton.

### Disconnection

Let's consider we have two successive NMEA messages:

```
$GPxxxxxxxxxxxxxxxCRLF            $GPxxxxxxxxxxxxxxxCRLF

time         t1            t2
------------------------------------------------------->
```

If the serial link is disconnected at t1 and reconnected at t2, the automaton will receive the start of the first message and then the second message. It can't know that the second message is a separate message. The resulting decoded message will be an incorrect message.

One way to protect the decoding against this type of problem is to check that the time between two successive received bytes is shorter than a limit (which depends on the serial link speed). If this limit is exceeded, the automaton is reset.