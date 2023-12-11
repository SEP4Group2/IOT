#include "dht11.h"
#include "humidity_temperature_controller.h"

uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal; // Variables for humidity and temperature

void get_dht11_sensor_data()
{
    DHT11_ERROR_MESSAGE_t data = dht11_get(&humidity_integer, &humidity_decimal, &temperature_integer, &temperature_decimal);
    if (data == DHT11_FAIL)
    {
        humidity_decimal = -99;
        humidity_integer = -99;
        temperature_decimal = -99;
        temperature_integer = -99;
    }
}

// return  temperature or humidity reading in JSON format
void get_formatted_temperature_reading(char *buffer)
{
    if (temperature_decimal == -99 && temperature_integer == -99)
    {
        sprintf(buffer, "\"Temperature\": \"Error!\"");
    }
    else
    {
        sprintf(buffer, "\\\"Temperature\\\": %d.%d",
                temperature_integer, temperature_decimal);
    }
    return buffer;
}

void get_formatted_humidity_reading(char *buffer)
{
    if (humidity_decimal == -99 && humidity_integer == -99)
    {
        sprintf(buffer, "\"Humidity\": \"Error!\"");
    }
    else
    {
        sprintf(buffer, "\\\"Humidity\\\": %d.%d",
                humidity_integer, humidity_decimal);
    }
    return buffer;
}

// return temperature or humidity  reading
uint16_t get_temperature_integer_reading()
{
    return temperature_integer;
}

uint16_t get_temperature_decimal_reading()
{
    return temperature_decimal;
}

uint16_t get_humidity_integer_reading()
{
    return humidity_integer;
}

uint16_t get_humidity_decimal_reading()
{
    return humidity_decimal;
}