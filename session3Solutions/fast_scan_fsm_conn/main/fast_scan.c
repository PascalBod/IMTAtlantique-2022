/* Scan Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

/*
    This example shows how to use the All Channel Scan or Fast Scan to connect
    to a Wi-Fi network.

    In the Fast Scan mode, the scan will stop as soon as the first network matching
    the SSID is found. In this mode, an application can set threshold for the
    authentication mode and the Signal strength. Networks that do not meet the
    threshold requirements will be ignored.

    In the All Channel Scan mode, the scan will end only after all the channels
    are scanned, and connection will start with the best network. The networks
    can be sorted based on Authentication Mode or Signal Strength. The priority
    for the Authentication mode is:  WPA2 > WPA > WEP > Open
*/
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"

/* Set the SSID and Password via project configuration, or can set directly here */
#define DEFAULT_SSID CONFIG_EXAMPLE_WIFI_SSID
#define DEFAULT_PWD CONFIG_EXAMPLE_WIFI_PASSWORD

#if CONFIG_EXAMPLE_WIFI_ALL_CHANNEL_SCAN
#define DEFAULT_SCAN_METHOD WIFI_ALL_CHANNEL_SCAN
#elif CONFIG_EXAMPLE_WIFI_FAST_SCAN
#define DEFAULT_SCAN_METHOD WIFI_FAST_SCAN
#else
#define DEFAULT_SCAN_METHOD WIFI_FAST_SCAN
#endif /*CONFIG_EXAMPLE_SCAN_METHOD*/

#if CONFIG_EXAMPLE_WIFI_CONNECT_AP_BY_SIGNAL
#define DEFAULT_SORT_METHOD WIFI_CONNECT_AP_BY_SIGNAL
#elif CONFIG_EXAMPLE_WIFI_CONNECT_AP_BY_SECURITY
#define DEFAULT_SORT_METHOD WIFI_CONNECT_AP_BY_SECURITY
#else
#define DEFAULT_SORT_METHOD WIFI_CONNECT_AP_BY_SIGNAL
#endif /*CONFIG_EXAMPLE_SORT_METHOD*/

#if CONFIG_EXAMPLE_FAST_SCAN_THRESHOLD
#define DEFAULT_RSSI CONFIG_EXAMPLE_FAST_SCAN_MINIMUM_SIGNAL
#if CONFIG_EXAMPLE_FAST_SCAN_WEAKEST_AUTHMODE_OPEN
#define DEFAULT_AUTHMODE WIFI_AUTH_OPEN
#elif CONFIG_EXAMPLE_FAST_SCAN_WEAKEST_AUTHMODE_WEP
#define DEFAULT_AUTHMODE WIFI_AUTH_WEP
#elif CONFIG_EXAMPLE_FAST_SCAN_WEAKEST_AUTHMODE_WPA
#define DEFAULT_AUTHMODE WIFI_AUTH_WPA_PSK
#elif CONFIG_EXAMPLE_FAST_SCAN_WEAKEST_AUTHMODE_WPA2
#define DEFAULT_AUTHMODE WIFI_AUTH_WPA2_PSK
#else
#define DEFAULT_AUTHMODE WIFI_AUTH_OPEN
#endif
#else
#define DEFAULT_RSSI -127
#define DEFAULT_AUTHMODE WIFI_AUTH_OPEN
#endif /*CONFIG_EXAMPLE_FAST_SCAN_THRESHOLD*/

static const char *TAG = "scan";

enum {
	ST_START_REQUESTED,
	ST_CONNECT_REQUESTED,
	ST_CONNECTED,
	ST_IP_SET,
} current_state = ST_START_REQUESTED;

static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
	switch (current_state) {
	case ST_START_REQUESTED:
		if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
			ESP_LOGI(TAG, "ST_START_REQUESTED - received WIFI_EVENT_STA_START");
			// If STA is started, we can try to connect.
			esp_wifi_connect();
			current_state = ST_CONNECT_REQUESTED;
			break;
		}
		// At this stage, some other event.
		ESP_LOGI(TAG, "ST_START_REQUESTED - unexpected event: %d", event_id);
		break;
	case ST_CONNECT_REQUESTED:
		if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_CONNECTED) {
			ESP_LOGI(TAG, "ST_CONNECT_REQUESTED - received WIFI_EVENT_STA_CONNECTED");
			// Nothing to do, apart from transitioning.
			current_state = ST_CONNECTED;
			break;
		}
		// It has been observed that we could receive a disconnected event as well.
		if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
			ESP_LOGI(TAG, "ST_CONNECT_REQUESTED - received WIFI_EVENT_STA_DISCONNECTED");
			// Let's try to reconnect.
			esp_wifi_connect();
			// Stay in same state.
			break;
		}
		// At this stage, some other event.
		ESP_LOGI(TAG, "ST_CONNECT_REQUESTED - unexpected event: %d", event_id);
		break;
	case ST_CONNECTED:
		if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
			ESP_LOGI(TAG, "ST_CONNECTED - received IP_EVENT_STA_GOT_IP");
			// Display IP address.
			ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
			ESP_LOGI(TAG, "Got ip:" IPSTR, IP2STR(&event->ip_info.ip));
			// Nothing to do, apart from transitioning.
			current_state = ST_IP_SET;
			break;
		}
		// We could receive a disconnected event as well.
		if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
			ESP_LOGI(TAG, "ST_CONNECTED - received WIFI_EVENT_STA_DISCONNECTED");
			// Let's try to reconnect.
			esp_wifi_connect();
			current_state = ST_CONNECT_REQUESTED;
			break;
		}
		// At this stage, some other event.
		ESP_LOGI(TAG, "ST_CONNECTED - unexpected event: %d", event_id);
		break;
	case ST_IP_SET:
		if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
			ESP_LOGI(TAG, "ST_IP_SET - received WIFI_EVENT_STA_DISCONNECTED");
			// Let's try to reconnect.
			esp_wifi_connect();
			current_state = ST_CONNECT_REQUESTED;
			break;
		}
		// At this stage, some other event.
		ESP_LOGI(TAG, "ST_IP_SET - unexpected event: %d", event_id);
		break;
	default:
		ESP_LOGE(TAG, "Unknown state: %d", current_state);
		// Reset automaton.
		current_state = ST_START_REQUESTED;
		// In a real application, we should also reset Wi-Fi state!
	}

}

/* Initialize Wi-Fi as sta and set scan method */
static void fast_scan(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL, NULL));

    // Initialize default station as network interface instance (esp-netif)
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    // Initialize and start WiFi
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = DEFAULT_SSID,
            .password = DEFAULT_PWD,
            .scan_method = DEFAULT_SCAN_METHOD,
            .sort_method = DEFAULT_SORT_METHOD,
            .threshold.rssi = DEFAULT_RSSI,
            .threshold.authmode = DEFAULT_AUTHMODE,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    ESP_LOGI(TAG, "Version 0.1");

    fast_scan();
}
