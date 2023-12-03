// uncomment the correct WIFI_SSID, WIFI_PASSWORD, TCP_IP and TCP_PORT for your setup and comment out the others.

// For Adrian
#define WIFI_SSID "ONEPLUS"
#define WIFI_PASSWORD "trudnehaslo"
#define TCP_IP "192.168.20.240"
#define TCP_PORT 23

// // For Kevin
// #define WIFI_SSID "iPhone Kevin"
// #define WIFI_PASSWORD "sockstobee"
// #define TCP_IP "172.20.10.9"

// // For Tina to test TCP Server
// #define WIFI_SSID "Stofa82982"
// #define WIFI_PASSWORD "digt41mudre46"
// #define TCP_IP "192.168.87.144"

// // Tina Jaššik
// #define WIFI_SSID "Tina Device"
// #define WIFI_PASSWORD "dzulia123"
// #define TCP_IP "172.20.10.4"

// #define WIFI_SSID "ONEPLUS"
// #define WIFI_PASSWORD "trudnehaslo"
// #define TCP_IP "192.168.20.240"
// #define TCP_PORT 23

const char *getWIFI_SSID()
{
    return WIFI_SSID;
}

const char *getWIFI_PASSWORD()
{
    return WIFI_PASSWORD;
}

const char *getTCP_IP()
{
    return TCP_IP;
}

int getTCP_PORT()
{
    return TCP_PORT;
}
