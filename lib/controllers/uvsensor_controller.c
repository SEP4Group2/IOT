#include "uvsensor.h"
#include "pc_comm.h"
#include "uvsensor_controller.h"

// return water level reading in JSON format
void get_formatted_uv_sensor_reading(char *buffer)
{
    sprintf(buffer, "\\\"UVLight\\\": %d",
            uvsensor_read());
}

// write water level reading in pc_commm
void print_uv_sensor_reading()
{
    pc_comm_send_string_blocking(uvsensor_read());
}

// return water level reading
uint16_t get_uv_sensor_reading()
{
    return uvsensor_read();
}