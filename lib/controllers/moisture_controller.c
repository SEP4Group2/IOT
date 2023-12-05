#include "moisture.h"
#include "pc_comm.h"
#include "moisture_controller.h"

// return moisture reading in JSON format
void get_formatted_moisture_reading(char *buffer)
{
    sprintf(buffer, "\"Moisture\": %d",
            moisture_read());
}

// write moisture reading in pc_commm
void print_moisture_reading()
{
    pc_comm_send_string_blocking(moisture_read());
}

// return moisture reading
uint16_t get_moisture_reading()
{
    return moisture_read();
}