# Session 1 exercises

## ESP32

The [ESP32](https://www.espressif.com/en/products/socs/esp32) is a microcontroller with Wi-Fi and Bluetooth connectivity. It has been created by [Espressif](https://www.espressif.com/en). It's part of the [ESP family](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/4/38).

[ESP-IDF](https://www.espressif.com/en/products/sdks/esp-idf) (IoT Development Framework) is Espressif's SDK (Software Development Kit) for developing applications for the ESP32.

## Overview of ESP-IDF

ESP-IDF is based on [FreeRTOS](https://www.freertos.org/) and provides a rich set of libraries.

FreeRTOS provides the means to architect an application: tasks, synchronization primitives, etc. The libraries provide the means to handle hardware resources: Wi-Fi, Bluetooth, Flash memory, interfaces, etc.

An application can be developped using three different types of environments:

* [Eclipse IDE](https://www.eclipse.org/ide/) (Integrated Development Environment), thanks to a [dedicated plugin](https://github.com/espressif/idf-eclipse-plugin/blob/master/README.md)
* [Visual Studio Code](https://code.visualstudio.com/), thanks to a [dedicated extension](https://marketplace.visualstudio.com/items?itemName=espressif.esp-idf-extension)
* the [command line](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html), with any code editor

ESP-IDF can be used in Linux, macOS or Windows.

In our exercises, we will use Eclipse with the dedicated plugin, in a Linux virtual machine. Linux is easier to use, and more adapted to embedded software development.

Programming language is C.

## Prerequisite

* An ESP32-DevKitC-32E board

## Create a Linux VM with Eclipse configured for ESP-IDF

Create a Linux virtual machine (VM) containing the Eclipse IDE configured for ESP-IDF. Two possibilities:

### Possibility 1 - step by step

Create the Linux VM and configure it step by step, as described by [this article](https://github.com/PascalBod/lm-esp32-eclipse)

### Possibility 2 - prebuilt VM

Install VirtualBox, as explained [here](https://github.com/PascalBod/lm-vm#virtualbox-installation).

Download the prebuilt VM from [Google Drive](https://drive.google.com/file/d/1fywW3ImaU_9D1ZQVogXougMhSMqiRUao/view?usp=sharing).

If your host machine runs Linux, add your user account to the `vboxusers` group:

```shell
$ sudo adduser developer vboxusers
```

If it runs macOS or Windows, chack this [forum thread](https://forums.virtualbox.org/viewtopic.php?f=35&t=82639), in case of problem with the USB port later on.

## Create a first sample application

Follow [these instructions](https://github.com/PascalBod/lm-esp32-eclipse#sample-application) to create a first sample application, based on the *hello_world* template.

Compile the project, flash it on the ESP32 board, and display the output of the application.

Note: the *hello_world* template is already created in Eclipse, in the prebuilt VM.

## Create a second sample application and modify it

Create a second sample application, based on the *wifi > scan* template. This template displays available Wi-Fi access points (AP).

Compile the project, flash it, and display the list of AP.

The template performs only one scan operation. Modify it so that it performs a scan operation every 10 seconds.

Doing this requires to use the [Wi-Fi driver](https://docs.espressif.com/projects/esp-idf/en/v4.4/esp32/api-guides/wifi.html) API (Application Programming Interface) along with some functions from the [ESP-NETIF](https://docs.espressif.com/projects/esp-idf/en/v4.4/esp32/api-reference/network/esp_netif.html) API and from the [event loop](https://docs.espressif.com/projects/esp-idf/en/v4.4/esp32/api-reference/system/esp_event.html) API. 

If you don't succeed, don't worry. But, in any case, take notes about how you addressed the problems you faced:

* how did you try to understand the meaning of the error messages?
* how did you search information in the Espressif documentation?
* how did you search information on the Internet?
* which websites did you discover? Which ones seem the most interesting ones?
* did you manage to get a first global view of the software execution environment?
* etc.