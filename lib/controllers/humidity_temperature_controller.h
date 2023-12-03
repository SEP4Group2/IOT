
void get_dht11_sensor_data();

// return  temperature or humidity reading in JSON format
const char *get_formatted_temperature_reading();

const char *get_formatted_humidity_reading();

// write  temperature or humidity reading in pc_commm
void print_humidity_reading();

void print_temperature_reading();

// return temperature or humidity  reading
uint16_t get_temperature_integer_reading();

uint16_t get_temperature_decimal_reading();

uint16_t get_humidity_integer_reading();

uint16_t get_humidity_decimal_reading();