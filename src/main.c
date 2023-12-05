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

  // // Should be moved to EEPROM controller and methods used from there
  // // EEPROM save test
  // int data = 67;
  // writeFloatToEEPROM(data);

  // // EEPROM read test
  // char buffers[128];

  // sprintf(buffers, "Data read from EEPROM: %d\n", readFloatFromEEPROM());
  // pc_comm_send_string_blocking(buffers);

  // initialize all sensor controllers
  init_controllers();

  // Connect to WiFi

  WIFI_ERROR_MESSAGE_t wifi_connection_status = wifi_command_join_AP(getWIFI_SSID(), getWIFI_PASSWORD());
  pc_comm_send_string_blocking(testWifiConnection(wifi_connection_status));

  void callCallback()
  {
    callbackTest(receiveParameter);
  }

  // Create TCP connection
  WIFI_ERROR_MESSAGE_t server_connection_status = wifi_command_create_TCP_connection(getTCP_IP(), getTCP_PORT(), callCallback, receiveParameter);
  if (server_connection_status == WIFI_OK)
  {
    pc_comm_send_string_blocking("\nREADY!\n\n");
  }
  pc_comm_send_string_blocking(testTcpConnection(server_connection_status));

  char buffer[128];
  char water_level_buffer[128];
  char moisture_buffer[128];
  char uv_sensor_buffer[128];
  char temperature_buffer[128];
  char humidity_buffer[128];

  timer_init_a(&button_1_check, 100);

  while (1)
  {
    // initialize the humidity and temperature sensor
    get_dht11_sensor_data();

    get_formatted_water_level_reading(water_level_buffer);
    get_formatted_moisture_reading(moisture_buffer);
    get_formatted_uv_sensor_reading(uv_sensor_buffer);
    get_formatted_temperature_reading(temperature_buffer);
    get_formatted_humidity_reading(humidity_buffer);

    sprintf(buffer, "{%s,%s,%s,%s,%s,}\n",
            water_level_buffer, moisture_buffer, uv_sensor_buffer, temperature_buffer, humidity_buffer);

    pc_comm_send_string_blocking(buffer);

    wifi_command_TCP_transmit((uint8_t *)buffer, strlen(buffer));

    // pump_run();

    // testing parameter received from callback
    //  pc_comm_send_string_blocking(receiveParameter);

    // callbackTest;

    _delay_ms(3000);
  }

  return 0;
}