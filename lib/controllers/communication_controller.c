#include "wifi.h"
#include "display.h"
#include "includes.h"
#include "communication_controller.h"
#include "display_controller.h"
#include "pump_controller.h"
#include "eeprom_controller.h"

#ifndef WINDOWS_TEST
#include "pc_comm.h"
#endif

extern int run_pump;

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

int data_acknowledged = 0;

int is_data_acknowledged()
{
    return data_acknowledged;
}

void callback(char *received_message_ptr)
{
    char *endptr;
    long received_message_long = strtol(received_message_ptr, &endptr, 10);

    long code = received_message_long / 100;
    int id;

    char buff[128];
    sprintf(buff, "\nCallBack >> Received: Message from Server is: %s\n", received_message_ptr);
    #ifndef WINDOWS_TEST
    pc_comm_send_string_blocking(buff);
    #endif

    switch (code)
    {
    case 161616:
        if (received_message_long == 16161601)
        {
           run_pump = 1;
        }
        if (received_message_long == 16161602)
        {
            data_acknowledged = 1;
        }
        break;

    case 999999:
        id = received_message_long % 100;

        writeFloatToEEPROM(id);
        break;

    default:
        writeToDisplay(received_message_ptr);
        break;
    }
}
