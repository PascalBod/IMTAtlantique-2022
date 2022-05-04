# Solution to session 3 exercise

## FSM states

The first step is to define the FSM states. According to the source code of the `fast_scan` example, and to the way a [Wi-Fi station works](https://docs.espressif.com/projects/esp-idf/en/v4.4.1/esp32/api-guides/wifi.html#esp32-wi-fi-station-general-scenario), we can think at the following states:
* Wi-Fi start has been requested - this is the state entered after the call to `esp_wifi_start()`, in order to wait for the result of the call, i.e. to wait for the end of the start phase. When this happens, connection to the access point can be requested
* Connection to the access point has been requested - in this state, the result of the connection is waited for. If the access point is available, the result should be the assignment of an IP address to the ESP32 (or, more precisely, to the network interface using the Wi-Fi connection)
* IP address assigned - the final state. Bu if the access point is shut down, or if the ESP32 moves too far from the access point, the Wi-Fi connection will be lost. If this happens, connection must be requested again

## Transitions

Resulting FSM can be:

```
+------------------+
|  Start requested |
+------------------+
          |
          |
          | WIFI_EVENT_STA_START
          | --------------------
          |  esp_wifi_connect()
          |
          v
+-------------------+<----------------------------------------------+
| Connect requested |<----------------+                             |
+-------------------+                 | WIFI_EVENT_STA_DISCONNECTED |
          |    |                      | --------------------------- |
          |    +----------------------+      esp_wifi_connect()     |
          |                                                         |
          | IP_EVENT_STA_GOT_IP                                     |
          | -------------------                                     |
          |                                                         |
          |                                                         |
          v                                                         |
+-------------------+                                               |
|   IP address set  |-----------------------------------------------+
+-------------------+
```

Resulting code is in `fast_scan_fsm` project, in [this repository](https://github.com/PascalBod/IMTAtlantique-2022/tree/main/session3Solutions).

## Improvement

When running the `fast_scan_fasm` application, an unexpected event is received, as pointed out by the following trace message:

```
scan: ST_CONNECT_REQUESTED - unexpected event: 4
```

The various possible values for a Wi-Fi event are declared in `esp_wifi_types.h:

```C
typedef enum {
    WIFI_EVENT_WIFI_READY = 0,           /**< ESP32 WiFi ready */
    WIFI_EVENT_SCAN_DONE,                /**< ESP32 finish scanning AP */
    WIFI_EVENT_STA_START,                /**< ESP32 station start */
    WIFI_EVENT_STA_STOP,                 /**< ESP32 station stop */
    WIFI_EVENT_STA_CONNECTED,            /**< ESP32 station connected to AP */
    WIFI_EVENT_STA_DISCONNECTED,         /**< ESP32 station disconnected from AP */
    WIFI_EVENT_STA_AUTHMODE_CHANGE,      /**< the auth mode of AP connected by ESP32 station changed */
```

According to the way the C language processes this enumeration, the value `4` corresponds to `WIFI_EVENT_STA_CONNECTED`. Going back to [ESP-IDF Wi-Fi documentation](https://docs.espressif.com/projects/esp-idf/en/v4.4.1/esp32/api-guides/wifi.html), we can see that, actually, the station code signals this event, which is currently not explicitly processed by our code.

Adding it to the FSM is quite easy, and left to the reader. A resulting possible code can be found in `fast_scan_fsm_conn` project, in [this repository](https://github.com/PascalBod/IMTAtlantique-2022/tree/main/session3Solutions).