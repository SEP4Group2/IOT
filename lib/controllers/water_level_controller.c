#include "hc_sr04.h"
#include "pc_comm.h"

// return water level reading in JSON format
const char *get_formatted_water_level_reading()
{
    char buffer[128];
    sprintf(buffer, "\"TankLevel\": %d",
            hc_sr04_takeMeasurement());
    return buffer;
}

// write water level reading in pc_commm
void print_water_level_reading()
{
    pc_comm_send_string_blocking(hc_sr04_takeMeasurement());
}

// return water level reading
uint16_t get_water_level_reading()
{
    return hc_sr04_takeMeasurement();
}