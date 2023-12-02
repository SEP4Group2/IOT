#include "wifi.h"
#include "display.h"
#include "includes.h"
#include "communication_controller.h"
#include "pc_comm.h"
#include "display_controller.h"

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

void callbackTest(char *received_message_ptr)
{

    writeToDisplay(received_message_ptr);

    switch (received_message_ptr[0])
    {
    case '0':
        pc_comm_send_string_blocking("\nGOOD\n");
        // Handle case '0', whatever is required
        break;

    case '1':
        pc_comm_send_string_blocking("\nBAD\n");
        // Handle case '1', whatever is required
        break;

    case '2':
        pc_comm_send_string_blocking("\nDEAD\n");
        // Handle case '2', whatever is required
        break;

    default:
        pc_comm_send_string_blocking("\nUnknown case\n");
        // Handle default case, whatever is required
        break;
    }
}
