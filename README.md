# IMT Atlantique - 2022

## Summary of session 1

* [Hardware progress](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/device-2)
    * In 35 years, processing power has been multiplied by 70 while cost has been divided by 38000. It's difficult to imagine what we will get over the next ten years
* [Memory, processing power and application](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/device-3)
  * In 1969, the mission to the Moon succeeded thanks to a computer with 72 KB of ROM and 4 KB of RAM
  * It's possible to make a lot with only few resources
  * Nowadays, a microcontroller costing less than 2€ is more powerful than the Apollo computer
* [Connected device architecture](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/device-4)
  * [Computer vs microcontroller](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/4/1)
    * Computer architecture: CPU, memory, interfaces with peripherals (an important one: disk drive), buses
    * In a computer, at boot time, a bootstrap program loads the OS into memory. Then the OS loads the applications
    * Thanks to the virtual memory mechanism provided by a computer OS, processes are isolated
    * A microcontroller: a whole computer on a chip
  * [Memory](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/4/6)
    * Evolution of ROM, which now can be erased and written
    * Memory map of a microcontroller
    * Many microcontroller provides a bootloader
  * [Architecture](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/4/9)
    * Overall architecture of a connected device
  * [Important characteristics](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/4/11)
    * Depend on the application
    * Some characteristics specific to the IoT
    * Hardware tools
    * Software tools
    * Support
  * [Common microcontroller families for connected devices](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/4/16)
    * Arm: a company that provides IP blocks, not microcontroller chips - The most widely used architecture
    * Many microcontroller manufacturers rely on Arm IP: Microchip, Nordic, NXP, STMicroelectronics, Texas Instruments, etc.
    * STMicroelectronics STM32 family
    * Cypress PSoc family. Microcontrollers with analog blocks
    * Espressif ESP family. Wi-Fi (+ Bluetooth) microcontrollers
    * MangOH boards: an open source design based on a Sierra Wireless cellular communication module running Linux
    * Microcontrollers for a few US$, demonstration/development boards for a few tens of US$

* [Session 1 exercises](session1Exercises.md)

## Summary of session 2

* [Solutions to session 1 exercises](https://github.com/PascalBod/IMTAtlantique-2022/tree/main/session1Solutions)

* [Software development](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/device-7)
  * [Cross development](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/7/1)
    * The application is developped for a target machine (microcontroller board) different from the development machine (desktop computer)
    * On the development machine: edit, compile, link and possibly emulate
    * With the development machine and the target board: flash, run, debug
    * Debugging may require some specific hardware tool
  * [Execution environments](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/7/5)
    * OS - mostly Linux based
      * Facilities similar to a desktop Linux, including package manager, GUI, etc.
      * Usual memory requirements: 512 MB to 1 GB of RAM, 1 GB to 8 GB of Flash (SD card <=> disk drive)
      * An MMU (Memory Management Unit) is required. Supports virtual memory and so process isolation
      * Linux can be built for no MMU
      * Many different distributions, often generated by Yocto
    * RTOS (Real Time OS)
      * Deterministic response time
      * Monolithic: RTOS + application can't be dissociated
      * A task may crash another task, or the whole application + RTOS
      * Usual memory requirements: a few KB of RAM, a few KB of Flash
      * Many different RTOSes
    * Bare metal
      * No OS, no RTOS, directly on the microcontroller
      * Abstraction layer may be provided (CMSIS, etc.)
  * [Interruptions and background task](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/7/23)
    * An interruption makes the microcontroller stop the current execution, save the context, run some dedicated short code, restore the context, resume the execution
    * Interrupt handler, Interrupt Service Routine (ISR)
    * Events that can generate interruptions: input signal change for a GPIO, timer events, UART events, A/D conversion events, etc. + some software events
    * Interrupt during an ISR execution: priorities
  * [Usual architecture of a bare metal application](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/7/36)
    * Saving energy: sleep modes
  * [Code example: UART RX](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/7/47)
  * [Useful design patterns](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/7/54)
    * Finite State Automaton (FSA) or Finite State Machine (FSM)
    * Ring buffer or circular buffer

* [Session 2 exercises](session2Exercises.md)

## Summary of session 3

* [Solutions to session 2 exercises](https://github.com/PascalBod/IMTAtlantique-2022/tree/main/session2Solutions)

* [Bare metal software development for STM32 microcontroller](https://pascalbod.github.io/stm32-dev-en-presentation/)
  * The target board
  * The target microcontroller
  * Harwdware and software documentation
  * [STM32CubeIDE](https://pascalbod.github.io/stm32-dev-en-presentation/#/21)
  * Build, run, debug
  * SWV

* [Session 3 exercise](https://github.com/PascalBod/IMTAtlantique-2022/blob/main/session3Exercises.md)

## Summary of session 4

* [Solution to session 3 exercise](https://github.com/PascalBod/IMTAtlantique-2022/tree/main/session3Solutions)

* [Application startup, stack, vector table, startup file, etc.](https://pascalbod.github.io/stm32-dev-en-presentation/#/30)
* [`serial` sample application: background task + ISR + atomicity for shared data structures](https://pascalbod.github.io/stm32-dev-en-presentation/#/53)
* [Data interchange](https://pascalbod.github.io/iot-en-presentation/#/communications-7)
  * message or stream?
  * UDP and many others are messages, TCP is stream
  * message format: the problems of transparency, endianness, and serialization (includes endianness)
  * ASN.1, Protocol Buffers, CBOR, other
  * message exchange: MQTT, CoAP, other
 
* [Session 4 exercise: UDP over Wi-Fi](https://github.com/PascalBod/espidf-udp)
  * This repository demonstrates step-by-step how to exchange messages between an ESP-IDF application and a PC application using UDP datagrams, through five successive steps
  * Go through the first three steps at least
  * No specific question. In the exercise report, provide a feedback about what you understood
