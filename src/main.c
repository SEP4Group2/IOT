#include "includes.h"
#include "pc_comm.h"
#include "dht11.h"
#include "display.h"
#include "leds.h"
#include "uvsensor.h"
#include "moisture.h"
#include "buttons.h"
#include "periodic_task.h"
#include "hc_sr04.h"
#include "wifi.h"
#include "avr/power.h"
#include "wifi.h"
#include "communication_controller.h"
#include "pump_controller.h"

#include <string.h>
#include <stdio.h>

//For Adrian
#define WIFI_SSID "ONEPLUS"
#define WIFI_PASSWORD "trudnehaslo"
#define TCP_IP "192.168.89.240"
#define TCP_PORT 23

//For Tina to test TCP Server
#define WIFI_SSID2 "Stofa82982"
#define WIFI_PASSWORD2 "digt41mudre46"
#define TCP_IP2 "192.168.87.144"


char receiveParameter[4];

int main(void)
{
  pc_comm_init(9600, NULL);
  pc_comm_send_string_blocking("LOADING!\n");

  

  wifi_init();
  display_init();
  display_setValues(13, 14, 10, 13);
  uvsensor_init();
  moisture_init();
  hc_sr04_init();
  buttons_init();
  dht11_init();

  // Connect to WiFi
  WIFI_ERROR_MESSAGE_t errorcode = wifi_command_join_AP(WIFI_SSID2, WIFI_PASSWORD2);
  pc_comm_send_string_blocking(testWifiConnection(errorcode));
  
  // errorcode = wifi_command_create_TCP_connection(TCP_IP, TCP_PORT, NULL, NULL);
  // testTcpConnection(errorcode);

 
  // Create TCP connection
  errorcode = wifi_command_create_TCP_connection(TCP_IP2, TCP_PORT, callbackTest, receiveParameter);

  uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal; // Variables for humidity and temperature

  // consider using only integer values for humidity and temperature instead of decimal values

  char caaray[128];

  pc_comm_send_string_blocking("READY!\n\n");

  // pump_run_timeout(2000);

  while (1)
  {

    DHT11_ERROR_MESSAGE_t error = dht11_get(&humidity_integer, &humidity_decimal, &temperature_integer, &temperature_decimal);
    if (error == DHT11_OK)
    {
      sprintf(caaray, "{\n\"TankLevel\": %d,\n\"Moisture\": %d,\n\"UVLight\": %d,\n\"Humidity\": %d.%d,\n\"Temperature\": %d.%d\n}\n\n",
              hc_sr04_takeMeasurement(), moisture_read(), uvsensor_read(), humidity_integer, humidity_decimal, temperature_integer, temperature_integer);
    }
    else if (error == DHT11_FAIL)
    {
      sprintf(caaray, "{\n\"TankLevel\": %d,\n\"Moisture\": %d,\n\"UVLight\": %d\n}\n\n",
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