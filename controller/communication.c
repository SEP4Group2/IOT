#include "wifi.h"
#include "includes.h"

const char *testWifiConnection(WIFI_ERROR_MESSAGE_t errorcode)
{
  static char buffer[100];

  switch (errorcode)
  {
  case WIFI_OK:
    strcpy(buffer, "\nWifi connect OK");
    break;
  case WIFI_FAIL:
    strcpy(buffer, "\nWifi connect FAIL");
    break;
  case WIFI_ERROR_RECEIVED_ERROR:
    strcpy(buffer, "\nWifi connect ERROR");
    break;
  case WIFI_ERROR_NOT_RECEIVING:
    strcpy(buffer, "\nWifi connect NOT RECEIVING");
    break;
  case WIFI_ERROR_RECEIVING_GARBAGE:
    strcpy(buffer, "\nWifi connect GARBAGE");
    break;
  default:
    strcpy(buffer, "\nUnknown Wifi error");
    break;
  }

  return buffer;
}

const char *testTcpConnection(WIFI_ERROR_MESSAGE_t errorcode)
{
  static char buffer[100];

  switch (errorcode)
  {
  case WIFI_OK:
    strcpy(buffer, "\nTcp connect OK");
    break;
  case WIFI_FAIL:
    strcpy(buffer, "\nTcp connect FAIL");
    break;
  case WIFI_ERROR_RECEIVED_ERROR:
    strcpy(buffer, "\nTcp connect ERROR");
    break;
  case WIFI_ERROR_NOT_RECEIVING:
    strcpy(buffer, "\nTcp connect NOT RECEIVING");
    break;
  case WIFI_ERROR_RECEIVING_GARBAGE:
    strcpy(buffer, "\nTcp connect GARBAGE");
    break;
  default:
    strcpy(buffer, "\nUnknown Tcp error");
    break;
  }

  return buffer;
}

void callBackTest(uint8_t receiveParameter)
{
  int part1, part2, part3, part4;
  char message[50];
  sprintf(message, "\nReceived: message from ESP32 is: %02d \n", receiveParameter);

  pc_comm_send_string_blocking(message);

  // Truncate and store each 2-digit part
  part4 = receiveParameter % 100;
  receiveParameter /= 100;

  part3 = receiveParameter % 100;
  receiveParameter /= 100;

  part2 = receiveParameter % 100;
  receiveParameter /= 100;

  part1 = receiveParameter; // The remaining part is stored in part1

  display_setValues(part1, part2, part3, part4);
}

// void callbackTest(uint8_t receiveParameter)
// {
//   switch (receiveParameter)
//   {
//   case '0':
//     pc_comm_send_string_blocking("\nResult 0\n");
//     break;
//   case '1':
//     pc_comm_send_string_blocking("\nTest complete\n");
//     break;
//   case '2':
//     pc_comm_send_string_blocking("\nPLANT GOOD\n");
//     display_setValues(9, 0, 0, 13);
//     break;
//   case '3':
//     pc_comm_send_string_blocking("\nPLANT BAD\n");
//     display_setValues(11, 10, 13, 17);
//     break;
//   case '4':
//     pc_comm_send_string_blocking("\nPLANT DEAD\n");
//     display_setValues(13, 14, 10, 13);
//     break;
//   case '5':
//     pc_comm_send_string_blocking("\nCAFE\n");
//     display_setValues(12, 10, 15, 14);
//     break;
//   case '6':
//     pc_comm_send_string_blocking("\nFACE\n");
//     display_setValues(15, 10, 12, 14);
//     break;
//   case '7':
//     pc_comm_send_string_blocking("\nDEAF\n");
//     display_setValues(13, 14, 10, 15);
//     break;
//   case '8':
//     pc_comm_send_string_blocking("\nDOC1\n");
//     display_setValues(13, 0, 12, 1);
//     break;
//   case '9':
//     pc_comm_send_string_blocking("\nCOOL\n");
//     display_setValues(12, 0, 0, 1);
//     break;
//   default:
//     // Handle unknown case if needed
//     break;
//   }
// }