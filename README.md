# IMT Atlantique - 2022

## Exercices for session 2

### Prerequisite

* An ESP32-DevKitC-32E board

### Create a Linux VM with Eclipse configured for ESP-IDF

Create a Linux virtual machine (VM) containing the Eclipse IDE configured for ESP-IDF. Two possibilities:

#### Possibility 1 - step by step

Create the Linux VM and configure it step by step, as described by [this article](https://github.com/PascalBod/lm-esp32-eclipse)

#### Possibility 2 - prebuilt VM

Install VirtualBox, as explained [here](https://github.com/PascalBod/lm-vm#virtualbox-installation).

Download the prebuilt VM from [Google Drive](https://drive.google.com/file/d/1fywW3ImaU_9D1ZQVogXougMhSMqiRUao/view?usp=sharing).

If your host machine runs Linux, add your user account to the `vboxusers` group:

```shell
$ sudo adduser developer vboxusers
```

If it runs macOS or Windows, chack this [forum thread](https://forums.virtualbox.org/viewtopic.php?f=35&t=82639), in case of problem with the USB port later on.

### Create a first sample application

Follow [these instructions](https://github.com/PascalBod/lm-esp32-eclipse#sample-application) to create a first sample application, based on the *hello_world* template.

Compile the project, flash it on the ESP32 board, and display the output of the application.

## Overview of ESP-IDF environment

ESP-IDF (*ESP* is for *ESPressif,* *IDF* is for *IoT Development Framework*) allows to to develop applications for ESP32-based boards. ESP-IDF integrates FreeRTOS, which allows to design application code using tasks, synchronization primitives, etc. Additionally, ESP-IDF provides a rich set of APIs, which are used to handle all hardware resources: Wi-Fi, Bluetooth, Flash memory, interfaces, etc.

An application can be developped using three different types of environments:
* Eclipse IDE (Integrated Development Environment), thanks to a dedicated plugin
* Visual Studio Code, thanks to a dedicated plugin
* the command line, with any code editor

ESP-IDF can be used in Linux, macOS or Windows.

In our exercises, we use Eclipse with the dedicated plugin, in a Linux virtual machine. Linux is easier to use, and more adapted to embedded software development.

## Reference documents

* [VirtualBox website](https://www.virtualbox.org/)
* [Linux Mint website](https://linuxmint.com/)
* Espressif:
  * [website](https://www.espressif.com/en)
  * [ESP-IDF Get Started webpage](https://docs.espressif.com/projects/esp-idf/en/v4.4/esp32/get-started/index.html#introduction)
  * [ESP32-DevKitC Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/v4.4/esp32/hw-reference/esp32/get-started-devkitc.html)

Note: the instructions in the *Create a first sample application* section above should be enough to let you create and run a first sample application.