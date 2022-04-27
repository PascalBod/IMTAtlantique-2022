# Session 3 exercises

## Connect to a Wi-Fi AP using an FSM

### Overview

The aim of this exercise it to modify an existing ESP32 example application that connects to a Wi-Fi access point (AP), in order to control all successive connection steps with a Finite State Machine (FSM).

### Example application

Create a new project from the *wifi > fast_scan* template (refer to session 1 exercises for information about how to create a project from a sample application).

### Configuration

The access point information (SSID and password) must be provided to the application. This can be done in the following way:
* in the Project Explorer view, double click on the `sdkconfig` file of the `fast_scan` project.
* in the SDK Configuration window that appears, select **Example Configuration**. This displays a list of fields
* fill in the **Wifi SSID** and **Wifi Password** fields at least, with the information of the Wi-Fi AP you will make the ESP32 connect to
* save the values (CTRL-S or **File > Save**)
* build the project
* flash the ESP32
* open a terminal and check the trace messages: the ESP32 should connect to the AP

### Architecture

The application works in the following way:
* `app_main` is started. It calls `fast_scan`
* `fast_scan` performs the follwoing successive tasks:
  * It initializes the network driver (`esp_netif_init`)
  * It creates what is named the default event loop (`esp_event_loop_create_default`)
  * It initializes the Wi-Fi driver (`esp_wifi_init`)
  * Then, it instructs ESP-IDF to send some specific events to the even loop. Additionally, it tells ESP-IDF to make the event loop call the `event_handler` function for each received event
* `event_handler` processes each event it receives

### What must be done

`event_handler` uses several `if...then...else...` statements to handle received events.

Replace the existing code with an FSM which will handle the events in the order they are received. Ensure that it can reconnect to the AP after a connection loss.

Following documentation provides required information:
* [Wi-Fi events](https://docs.espressif.com/projects/esp-idf/en/v4.4.1/esp32/api-guides/wifi.html)
* [The event loop](https://docs.espressif.com/projects/esp-idf/en/v4.4.1/esp32/api-reference/system/esp_event.html)