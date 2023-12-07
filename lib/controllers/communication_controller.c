#include "wifi.h"
#include "display.h"
#include "includes.h"
#include "communication_controller.h"
#include "pc_comm.h"
#include "display_controller.h"
#include "pump_controller.h"
#include "eeprom_controller.h"

char *testWifiConnection(WIFI_ERROR_MESSAGE_t errorcode)
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

char *testTcpConnection(WIFI_ERROR_MESSAGE_t errorcode)
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

void callback(char *received_message_ptr)
{
    char *endptr;
    long received_message_long = strtol(received_message_ptr, &endptr, 10);

    int code = received_message_long / 100;
    int id = (int)received_message_long % 100;

    char buff[128];
    sprintf(buff, "Received: INT from ESP8266 is: %d \n", code);
    pc_comm_send_string_blocking(buff);

    switch (code)
    {
    case 161616:
        if (received_message_long == 16161601)
        {
            pump_run();
            pc_comm_send_string_blocking("RUNNING THE PUMP");
        }
        if (received_message_long == 16161602)
        {
            
        }
        break;

    case 999999:
        writeFloatToEEPROM(id);
        pc_comm_send_string_blocking("Writing in memory id: " + id);
        break;

    default:
        writeToDisplay(received_message_ptr);
        break;
    }

    char buffer[128];
    sprintf(buffer, "Communication controller: %s\n", received_message_ptr);
    pc_comm_send_string_blocking(buffer);
}

