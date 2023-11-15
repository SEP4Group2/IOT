#include "wifi.h"
#include "includes.h"

const char* testWifiConnection(WIFI_ERROR_MESSAGE_t errorcode, const char* source) 
{
    static char buffer[100]; 

    switch (errorcode) {
        case WIFI_OK:
            strcpy(buffer, "\nWifi connect OK to ");
            break;
        case WIFI_FAIL:
            strcpy(buffer, "\nWifi connect FAIL to ");
            break;
        case WIFI_ERROR_RECEIVED_ERROR:
            strcpy(buffer, "\nWifi connect ERROR to ");
            break;
        case WIFI_ERROR_NOT_RECEIVING:
            strcpy(buffer, "\nWifi connect NOT RECEIVING to ");
            break;
        case WIFI_ERROR_RECEIVING_GARBAGE:
            strcpy(buffer, "\nWifi connect GARBAGE to ");
            break;
        default:
            strcpy(buffer, "\nUnknown error to ");
            break;
    }

    strcat(buffer, source);

    return buffer;
}
