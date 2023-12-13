#include "uvsensor.h"
#include "uvsensor_controller.h"
#include <stdio.h>

// return water level reading in JSON format
void get_formatted_uv_sensor_reading(char *buffer)
{
    sprintf(buffer, "\\\"UVLight\\\": %u",
            uvsensor_read());
}

// return water level reading
uint16_t get_uv_sensor_reading()
{
    return uvsensor_read();
}