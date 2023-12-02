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
#include "avr/eeprom.h"

#include <string.h>
#include <stdio.h>

//WIFI configurations
//For Adrian
#define WIFI_SSID "ONEPLUS"
#define WIFI_PASSWORD "trudnehaslo"
#define TCP_IP "192.168.20.240"
#define TCP_PORT 23

//For Tina to test TCP Server
#define WIFI_SSID2 "Stofa82982"
#define WIFI_PASSWORD2 "digt41mudre46"
#define TCP_IP2 "192.168.87.144"

//Tina Jaššik
#define WIFI_SSID3 "Tina Device"
#define WIFI_PASSWORD3 "dzulia123"
#define TCP_IP3 "172.20.10.4"


char receiveParameter[16];


//Saving ID to EEPROM
//Should be moved to another class
#define EEPROM_FLOAT_START_ADDRESS 4090

void writeFloatToEEPROM(int data)
{
  eeprom_write_block(&data, (void *)EEPROM_FLOAT_START_ADDRESS, 4);
}

int readFloatFromEEPROM()
{
  int data;
  eeprom_read_block(&data, (const void *)EEPROM_FLOAT_START_ADDRESS, 4);
  return data;
}




int main(void)
{

  //Should probably be moved to communication controller
  //Init for pc_comm
  pc_comm_init(9600, NULL);
  pc_comm_send_string_blocking("LOADING!\n");



  //Should be moved to EEPROM controller and methods used from there
  //EEPROM save test
  // int data = 69;
  // writeFloatToEEPROM(data);

  //EEPROM read test
  char buffers[128];

  sprintf(buffers, "Data read from EEPROM: %d\n", readFloatFromEEPROM()); 
  pc_comm_send_string_blocking(buffers);

  

  wifi_init();
  display_init();
  display_setValues(13, 14, 10, 13);
  uvsensor_init();
  moisture_init();
  hc_sr04_init();
  buttons_init();
  dht11_init();

  // Connect to WiFi
  WIFI_ERROR_MESSAGE_t errorcode = wifi_command_join_AP(WIFI_SSID, WIFI_PASSWORD);
  pc_comm_send_string_blocking(testWifiConnection(errorcode));
  
  // errorcode = wifi_command_create_TCP_connection(TCP_IP, TCP_PORT, NULL, NULL);
  // testTcpConnection(errorcode);

  void callCallback()
  {
    callbackTest(receiveParameter);
    char buffer[128];
    char buffer2[128];
    char buffer3[128];
    sprintf(buffer, "callCallback  Communication controller &: %d\n", &receiveParameter);
    sprintf(buffer2, "callCallback  Communication controller: %d\n", receiveParameter);
    sprintf(buffer3, "callCallback  Communication controller*: %d\n", *receiveParameter);


    pc_comm_send_string_blocking(buffer);
    pc_comm_send_string_blocking(buffer2);
    pc_comm_send_string_blocking(buffer3);
  }
  
  // Create TCP connection
  errorcode = wifi_command_create_TCP_connection(TCP_IP, TCP_PORT, callCallback, receiveParameter);


  

  uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal; // Variables for humidity and temperature

  // consider using only integer values for humidity and temperature instead of decimal values

  char caaray[128];

  //Should be moved to communication controller as a part of WIFI init method
  pc_comm_send_string_blocking("READY!\n\n");

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

    // pump_run();


    //testing parameter received from callback
    // pc_comm_send_string_blocking(receiveParameter);

    // callbackTest;

    _delay_ms(3000);
  }

  return 0;
}