#include "includes.h"
#include "pc_comm.h"
#include "dht11.h"
#include "display.h"
#include "leds.h"
#include "uvsensor.h"
#include "moisture.h"
#include "buzzer.h"
#include "buttons.h"
#include "periodic_task.h"
#include "adxl345.h"
#include "hc_sr04.h"
#include "wifi.h"
#include "avr/power.h"
#include "pir.h"
#include "tone.h"
#include "servo.h"
#include "wifi.h"
#include "pump.h"

#include <string.h>
#include <stdio.h>

#define WIFI_SSID "iPhone Kevin "
#define WIFI_PASSWORD "sockstobee"
#define TCP_IP "20.107.165.243"
#define TCP_PORT 23

void handle_wifi_error(WIFI_ERROR_MESSAGE_t errorcode, const char* source) {
  char buffer[100]; // Buffer to store the error message

  switch (errorcode) {
    case WIFI_OK:
      sprintf(buffer, "\nWifi connect OK to %s\n", source);
      break;
    case WIFI_FAIL:
      sprintf(buffer, "\nWifi connect FAIL to %s\n", source);
      break;
    case WIFI_ERROR_RECEIVED_ERROR:
      sprintf(buffer, "\nWifi connect ERROR to %s\n", source);
      break;
    case WIFI_ERROR_NOT_RECEIVING:
      sprintf(buffer, "\nWifi connect NOT RECEIVING to %s\n", source);
      break;
    case WIFI_ERROR_RECEIVING_GARBAGE:
      sprintf(buffer, "\nWifi connect GARBAGE to %s\n", source);
      break;
    default:
      sprintf(buffer, "\nUnknown error to %s\n", source);
      break;
  }

  pc_comm_send_string_blocking(buffer); // Send the error message
}

int main(void)
{
pc_comm_init(9600, NULL);
  pc_comm_send_string_blocking("LOADING!\n");

  wifi_init();

  // Connect to WiFi
  WIFI_ERROR_MESSAGE_t errorcode = wifi_command_join_AP(WIFI_SSID, WIFI_PASSWORD);
  handle_wifi_error(errorcode, WIFI_SSID);

  // Create TCP connection
  errorcode = wifi_command_create_TCP_connection(TCP_IP, TCP_PORT, NULL, NULL);
  handle_wifi_error(errorcode,TCP_IP );

  display_init();
  leds_init();
  uvsensor_init();
  moisture_init();
  pump_init();
  hc_sr04_init();
  buttons_init();
  dht11_init();

  display_setValues(16, 10, 16, 17);

  char caaray[128];
  uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal; // Variables for humidity and temperature

// consider using only integer values for humidity and temperature instead of decimal values

  pc_comm_send_string_blocking("READY!\n\n");

  pump_run_timeout(2000);

  while (1)
  {

    DHT11_ERROR_MESSAGE_t error = dht11_get(&humidity_integer, &humidity_decimal, &temperature_integer, &temperature_decimal);
    if (error == DHT11_OK)
    {
      sprintf(caaray, "{\n\"Tank Level\": %d,\n\"Moisture\": %d,\n\"UV\": %d,\n\"Humidity\": %d.%d,\n\"Temperature\": %d.%d\n}\n\n",
              hc_sr04_takeMeasurement(), moisture_read(), uvsensor_read(), humidity_integer, humidity_decimal, temperature_integer, temperature_integer);
    }
    else if (error == DHT11_FAIL)
    {
      sprintf(caaray, "{\n\"Measurment\": %d,\n\"Moisture\": %d,\n\"UV\": %d,\n}\n\n",
              hc_sr04_takeMeasurement(), moisture_read(), uvsensor_read());
    }

    int length = strlen(caaray);

    pc_comm_send_string_blocking(caaray);
    wifi_command_TCP_transmit((uint8_t *)caaray, length);

    _delay_ms(3000);
  }

  return 0;
}