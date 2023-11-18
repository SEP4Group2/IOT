#include "wifi.h"
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