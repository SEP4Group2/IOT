#include "wifi.h"
#include "display.h"
#include "includes.h"

const char* testWifiConnection(WIFI_ERROR_MESSAGE_t errorcode) 
{
    static char buffer[100]; 

    switch (errorcode) {
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


const char* testTcpConnection(WIFI_ERROR_MESSAGE_t errorcode) 
{
    static char buffer[100]; 

    switch (errorcode) {
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

const char* callback(uint8_t receiveParameter)
{
  switch (receiveParameter)
  {
    case 'GOOD':
      pc_comm_send_string_blocking("\nGOOD\n");
      return "\nPLANT GOOD\n";
    case 'BAD':
      pc_comm_send_string_blocking("\nBAD\n");
      return "\nPLANT BAD\n";
    case 'DEAD':
      pc_comm_send_string_blocking("\nDEAD\n");
      return "\nPLANT DEAD\n";
    default:
      pc_comm_send_string_blocking("\nUnknown case\n");
      return "\nUnknown case\n";
  }
}


