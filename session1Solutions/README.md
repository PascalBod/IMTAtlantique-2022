# Solutions to session 1 exercises

## Wi-Fi scan

### Adding a loop

If we try to simply add a loop around the call to the `wifi_scan` function like this:

```C
    while (true)
    {
        wifi_scan();
        sleep(10);      // Wait 10 seconds before next scan.
    }
```

we get the following error messages for the second call:

```
ESP_ERROR_CHECK failed: esp_err_t 0x103 (ESP_ERR_INVALID_STATE) at 0x40088334
0x40088334: _esp_error_check_failed at /home/developer/DevTools/esp-idf-v4.4/components/esp_system/esp_err.c:42

file: "../main/scan.c" line 113
func: wifi_scan
expression: esp_event_loop_create_default()

abort() was called at PC 0x40088337 on core 0
0x40088337: _esp_error_check_failed at /home/developer/DevTools/esp-idf-v4.4/components/esp_system/esp_err.c:43



Backtrace:0x400819e6:0x3ffba4e00x40088341:0x3ffba500 0x4008ede6:0x3ffba520 0x40088337:0x3ffba590 0x400d5ef9:0x3ffba5b0 0x400d6124:0x3ffba9c0 0x4013c199:0x3ffba9e0 0x4008b505:0x3ffbaa00 
0x400819e6: panic_abort at /home/developer/DevTools/esp-idf-v4.4/components/esp_system/panic.c:402

0x40088341: esp_system_abort at /home/developer/DevTools/esp-idf-v4.4/components/esp_system/esp_system.c:121

0x4008ede6: abort at /home/developer/DevTools/esp-idf-v4.4/components/newlib/abort.c:46

0x40088337: _esp_error_check_failed at /home/developer/DevTools/esp-idf-v4.4/components/esp_system/esp_err.c:43

0x400d5ef9: wifi_scan at /home/developer/eclipse-workspace/scan/build/../main/scan.c:113 (discriminator 1)

0x400d6124: app_main at /home/developer/eclipse-workspace/scan/build/../main/scan.c:155 (discriminator 1)

0x4013c199: main_task at /home/developer/DevTools/esp-idf-v4.4/components/freertos/port/port_common.c:129 (discriminator 2)

0x4008b505: vPortTaskWrapper at /home/developer/DevTools/esp-idf-v4.4/components/freertos/port/xtensa/port.c:131





ELF file SHA256: 3c04f35483f27d72

Rebooting...
```

### Looking for the solution

According to the first lines, the call to `esp_event_loop_create_default` fails. 

The error messages contain some hints:
* The type of error: `ESP_ERR_INVALID_STATE`. So, when making the second call, ESP-IDF was not in a right state
* Number of the line at the origin of the problem, name of associated function, etc. Here, the problem occurs when `esp_event_loop_create_default` is called a second time

Now let's check the documentation; in our case, ESP-IDF documentation: 
* The [Wi-Fi driver documentation](https://docs.espressif.com/projects/esp-idf/en/v4.4/esp32/api-guides/wifi.html) mentions the default event loop, and provides a link to some documentation. A diagram and the text mention a *deinit phase*
* The [default event loop documentation](https://docs.espressif.com/projects/esp-idf/en/v4.4/esp32/api-reference/system/esp_event.html#esp-event-default-loops) the list of available functions. Among them: `esp_event_loop_delete_default`
* The problem appears the second time the scan function is called, and the libraries provide some functions to deinit/deallocate: a logical assumption is that resources allocated by the first call must be deallocated before a second call is performed. Actually, this is the solution.

Resulting code: see [scan_solution project](https://github.com/PascalBod/IMTAtlantique-2022/tree/main/session1Solutions/scan_solution).

ESP-IDF documentation website is the primary source of information. The ESP32 ecosystem provides additional resources:
* [ESP32 forum](https://esp32.com/)
* [stackoverflow for ESP32](https://stackoverflow.com/questions/tagged/esp32)
* [reddit for ESP32](https://www.reddit.com/r/esp32/)
* [ESP-IDF source code on GitHub](https://github.com/espressif/esp-idf)
* various other websites
* etc.

And of course your preferred web search engine.