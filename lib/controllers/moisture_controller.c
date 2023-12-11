#include "moisture.h"
#include "moisture_controller.h"

// return moisture reading in JSON format
void get_formatted_moisture_reading(char *buffer)
{
    sprintf(buffer, "\\\"Moisture\\\": %u",
            moisture_read());
}

// return moisture reading
uint16_t get_moisture_reading()
{
    return moisture_read();
}