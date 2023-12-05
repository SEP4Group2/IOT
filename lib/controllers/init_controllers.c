// Description: Initializes all controllers.
#include "init_controllers.h"

#include "dht11.h"
#include "display.h"
#include "uvsensor.h"
#include "moisture.h"
#include "buttons.h"
#include "hc_sr04.h"
#include "wifi.h"
#include "pump.h"

void init_controllers()
{
    wifi_init();
    display_init();
    uvsensor_init();
    moisture_init();
    hc_sr04_init();
    buttons_init();
    dht11_init();
    pump_init();
}