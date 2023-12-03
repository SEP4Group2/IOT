#include "includes.h"
#include "pc_comm.h"
#include "display.h"
#include "leds.h"
#include "buttons.h"
#include "periodic_task.h"
#include "wifi.h"
#include "avr/power.h"
#include "avr/eeprom.h"

#include "communication_controller.h"
#include "pump_controller.h"
#include "wifi_settings.h"
#include "init_controllers.h"
#include "humidity_temperature_controller.h"
#include "water_level_controller.h"
#include "uvsensor_controller.h"
#include "moisture_controller.h"
#include "eeprom_controller.h"

#include <string.h>
#include <stdio.h>

char receiveParameter[16];

int main(void)
{

  // Should probably be moved to communication controller
  // Init for pc_comm
  pc_comm_init(9600, NULL);
  pc_comm_send_string_blocking("LOADING!\n");

  // Should be moved to EEPROM controller and methods used from there
  // EEPROM save test
  int data = 67;
  writeFloatToEEPROM(data);

  // EEPROM read test
  char buffers[128];

  sprintf(buffers, "Data read from EEPROM: %d\n", readFloatFromEEPROM());
  pc_comm_send_string_blocking(buffers);

  // initialize all sensor controllers
  init_controllers();

  // Connect to WiFi

  WIFI_ERROR_MESSAGE_t errorcode = wifi_command_join_AP(getWIFI_SSID(), getWIFI_PASSWORD());
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
  errorcode = wifi_command_create_TCP_connection(getTCP_IP(), getTCP_PORT(), callCallback, receiveParameter);

  uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal; // Variables for humidity and temperature

  char caaray[128];

  pc_comm_send_string_blocking("\nREADY!\n\n");

  timer_init_a(&button_1_check, 100);

  while (1)
  {

    // initialize the humidity and temperature sensor
    get_dht11_sensor_data();

    sprintf(caaray, "{%d,%d,%d%,%d,%d}",
            get_formatted_water_level_reading(), get_formatted_moisture_reading(), get_formatted_uv_sensor_reading(), get_formatted_temperature_reading(), get_formatted_humidity_reading());

    pc_comm_send_string_blocking(caaray);
    wifi_command_TCP_transmit((uint8_t *)caaray, strlen(caaray));

    // pump_run();

    // testing parameter received from callback
    //  pc_comm_send_string_blocking(receiveParameter);

    // callbackTest;

    _delay_ms(3000);
  }

  return 0;
}