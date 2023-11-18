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
#include "communication.h"

#include <string.h>
#include <stdio.h>

#define WIFI_SSID "ONEPLUS_co_apmkvh"
#define WIFI_PASSWORD "trudnehaslo"
#define TCP_IP "192.168.89.240"
#define TCP_PORT 23

uint8_t receiveTest[1];

void callbackTest()
{
  switch (receiveTest[0])
  {
    case '0':
      pc_comm_send_string_blocking("\nResult 0\n");
      break;
    case '1':
      pc_comm_send_string_blocking("\nTest complete\n");
      break;
    case '2':
      pc_comm_send_string_blocking("\nPLANT GOOD\n");
      display_setValues(9, 0, 0, 13);
      break;
    case '3':
      pc_comm_send_string_blocking("\nPLANT BAD\n");
      display_setValues(11, 10, 13, 17);
      break;
    case '4':
      pc_comm_send_string_blocking("\nPLANT DEAD\n");
      display_setValues(13, 14, 10, 13);
      break;
    case '5':
      pc_comm_send_string_blocking("\nCAFE\n");
      display_setValues(12, 10, 15, 14);
      break;
    case '6':
      pc_comm_send_string_blocking("\nFACE\n");
      display_setValues(15, 10, 12, 14);
      break;
    case '7':
      pc_comm_send_string_blocking("\nDEAF\n");
      display_setValues(13, 14, 10, 15);
      break;
    case '8':
      pc_comm_send_string_blocking("\nDOC1\n");
      display_setValues(13, 0, 12, 1);
      break;
    case '9':
      pc_comm_send_string_blocking("\nCOOL\n");
      display_setValues(12, 0, 0, 1);
      break;
    default:
      // Handle unknown case if needed
      break;
  }
}

int main(void)
{
  pc_comm_init(9600, NULL);
  pc_comm_send_string_blocking("LOADING!\n");

  wifi_init();

  // Connect to WiFi
  WIFI_ERROR_MESSAGE_t errorcode = wifi_command_join_AP(WIFI_SSID, WIFI_PASSWORD);
  testWifiConnection(errorcode);

  errorcode = wifi_command_create_TCP_connection(TCP_IP, TCP_PORT, NULL, NULL);
  testTcpConnection(errorcode);

  // Create TCP connection
  errorcode = wifi_command_create_TCP_connection(TCP_IP, TCP_PORT, callbackTest, receiveTest);
  handle_wifi_error(errorcode, TCP_IP);

  display_init();
  leds_init();
  uvsensor_init();
  moisture_init();
  pump_init();
  hc_sr04_init();
  buttons_init();
  dht11_init();

  display_setValues(13, 14, 10, 13);

  char caaray[128];
  uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal; // Variables for humidity and temperature

  // consider using only integer values for humidity and temperature instead of decimal values

  pc_comm_send_string_blocking("READY!\n\n");

  // pump_run_timeout(2000);

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

    // callbackTest;

    _delay_ms(3000);
  }

  return 0;
}