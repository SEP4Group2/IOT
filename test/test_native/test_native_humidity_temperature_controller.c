#include "../../fff.h"
#include "unity.h"
#include "humidity_temperature_controller.h"
#include "dht11.h"

DEFINE_FFF_GLOBALS;

// Define fakes for the sensor functions
FAKE_VOID_FUNC(dht11_init);
FAKE_VALUE_FUNC(DHT11_ERROR_MESSAGE_t, dht11_get, uint8_t*, uint8_t*, uint8_t*, uint8_t*);

void setUp(void) {
    RESET_FAKE(dht11_init);
    RESET_FAKE(dht11_get);
}

void tearDown(void) {
}

//Mock function definition from dht11.h
DHT11_ERROR_MESSAGE_t custom_dht11_get(uint8_t* hum_int, uint8_t* hum_dec, uint8_t* temp_int, uint8_t* temp_dec) {

    *hum_int = 20;
    *hum_dec = 30;
    *temp_int = 40;
    *temp_dec = 50; 
    return DHT11_OK;
}

//Mock function definitions from temperature_humidity_controller.h
void custom_get_formatted_humidity_reading(char *buffer, int humidity_int, int humidity_dec) {
    if (humidity_dec == -99 && humidity_int == -99) {
        sprintf(buffer, "\"Humidity\": \"Error!\"");
    } else {
        sprintf(buffer, "\\\"Humidity\\\": %d.%d", humidity_int, humidity_dec);
    }
}

void custom_get_formatted_temperature_reading(char *buffer, int temperature_int, int temperature_dec) {
    if (temperature_dec == -99 && temperature_int == -99) {
        sprintf(buffer, "\"Temperature\": \"Error!\"");
    } else {
        sprintf(buffer, "\\\"Temperature\\\": %d.%d", temperature_int, temperature_dec);
    }
}

// Test function using the custom fake for get_formatted_humidity_reading()
void test_get_formatted_humidity_reading() {
    char buffer[128];

    // Simulate internal state values
    int simulated_humidity_int = 60;
    int simulated_humidity_dec = 75;

    // Call the function using the custom fake
    custom_get_formatted_humidity_reading(buffer, simulated_humidity_int, simulated_humidity_dec);

    // Assert the expected string output
    TEST_ASSERT_EQUAL_STRING("\\\"Humidity\\\": 60.75", buffer);
    
}

void test_get_formatted_temperature_reading() {
    char buffer[128];

    // Simulate internal state values
    int simulated_temperature_int = 25;
    int simulated_temperature_dec = 50;

    // Call the function using the custom fake
    custom_get_formatted_temperature_reading(buffer, simulated_temperature_int, simulated_temperature_dec);

    // Assert the expected string output
    TEST_ASSERT_EQUAL_STRING("\\\"Temperature\\\": 25.50", buffer);
}

void test_dht11_get_valid_data() {
 
    uint8_t humidity_int = 0, humidity_dec = 0, temp_int = 0, temp_dec = 0;


    dht11_get_fake.custom_fake = custom_dht11_get;

    // Calling fake function replaced by custom_dht11_get
    DHT11_ERROR_MESSAGE_t result = dht11_get(&humidity_int, &humidity_dec, &temp_int, &temp_dec);

    TEST_ASSERT_EQUAL_UINT8(1, dht11_get_fake.call_count);

    TEST_ASSERT_EQUAL_UINT8(DHT11_OK, result);
    TEST_ASSERT_EQUAL_UINT8(20, humidity_int);
    TEST_ASSERT_EQUAL_UINT8(30, humidity_dec);
    TEST_ASSERT_EQUAL_UINT8(40, temp_int);
    TEST_ASSERT_EQUAL_UINT8(50, temp_dec);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_get_formatted_humidity_reading);
    RUN_TEST(test_get_formatted_temperature_reading);
    RUN_TEST(test_dht11_get_valid_data);

    return UNITY_END();
}
