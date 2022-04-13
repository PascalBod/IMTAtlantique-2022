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

* [Exercises for session 2](exercisesForSession2.md)
* [Solutions for session 2](https://github.com/PascalBod/IMTAtlantique-2022/tree/main/solutionsForSession2)

## Summary of session 2

* [Exercises for session 3](exercisesForSession3.md)