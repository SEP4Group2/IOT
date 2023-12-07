#include "hc_sr04.h"
#include "pc_comm.h"

// return water level reading in JSON format
void get_formatted_water_level_reading(char *buffer)
{
    sprintf(buffer, "\\\"TankLevel\\\": %d",
            hc_sr04_takeMeasurement());
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