#include "hc_sr04.h"
#include "pc_comm.h"
#include "water_level_controller.h"

// return water level reading in JSON format
void get_formatted_water_level_reading(char *buffer)
{
    sprintf(buffer, "\"TankLevel\": %u",
            hc_sr04_takeMeasurement());
}

// return water level reading
uint16_t get_water_level_reading()
{
    return hc_sr04_takeMeasurement();
}