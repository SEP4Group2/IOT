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

int main(void)
{

  pc_comm_init(9600, NULL);

  pc_comm_send_string_blocking("LOADING!\n");

  wifi_init();

  WIFI_ERROR_MESSAGE_t errorcode = wifi_command_join_AP("iPhone Kevin ", "sockstobee");
  if (errorcode == WIFI_OK)
  {
    pc_comm_send_string_blocking("\nWifi connect OK\n");
  }
  else if (errorcode == WIFI_FAIL)
  {
    pc_comm_send_string_blocking("\nWifi connect FAIL\n");
  }
  else if (errorcode == WIFI_ERROR_RECEIVED_ERROR)
  {
    pc_comm_send_string_blocking("\nWifi connect ERROR\n");
  }
  else if (errorcode == WIFI_ERROR_NOT_RECEIVING)
  {
    pc_comm_send_string_blocking("\nWifi connect NOT RECEIVING\n");
  }
  else if (errorcode == WIFI_ERROR_RECEIVING_GARBAGE)
  {
    pc_comm_send_string_blocking("\nWifi connect GARBAGE\n");
  }

  errorcode = wifi_command_create_TCP_connection("20.107.165.243", 23, NULL, NULL);
  if (errorcode == WIFI_OK)
  {
    pc_comm_send_string_blocking("Wifi tcp OK\n\n");
  }
  else if (errorcode == WIFI_FAIL)
  {
    pc_comm_send_string_blocking("Wifi tcp FAIL\n\n");
  }
  else if (errorcode == WIFI_ERROR_RECEIVED_ERROR)
  {
    pc_comm_send_string_blocking("Wifi tcp ERROR\n\n");
  }
  else if (errorcode == WIFI_ERROR_NOT_RECEIVING)
  {
    pc_comm_send_string_blocking("Wifi tcp NOT RECEIVING\n\n");
  }
  else if (errorcode == WIFI_ERROR_RECEIVING_GARBAGE)
  {
    pc_comm_send_string_blocking("Wifi tcp GARBAGE\n\n");
  }

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