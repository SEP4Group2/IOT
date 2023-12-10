#ifdef NATIVE_TEST

#include "unity.h"
#include "../../fff.h"
#include "humidity_temperature_controller.h"
#include "dht11.h"

DEFINE_FFF_GLOBALS;

void setUp(void)
{
    // Initialize the fakes
    FFF_RESET_HISTORY();
}

void tearDown(void)
{
    // Clean up after the test
}


 // @brief DHT11 Error messages.
uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal; // Variables for humidity and temperature

// Mocking DHT11 functions
FAKE_VALUE_FUNC(DHT11_ERROR_MESSAGE_t, dht11_get, uint8_t*, uint8_t*, uint8_t*, uint8_t*);

void testGetDHT11SensorData_Success(void) {
    // Set up fake data
    uint8_t fakeHumidityInteger = 50;
    uint8_t fakeHumidityDecimal = 5;
    uint8_t fakeTemperatureInteger = 25;
    uint8_t fakeTemperatureDecimal = 3;

    // Set the return values for the fake dht11_get function
    dht11_get_fake.return_val = DHT11_OK;
    dht11_get_fake.arg0_val = &fakeHumidityInteger;
    dht11_get_fake.arg1_val = &fakeHumidityDecimal;
    dht11_get_fake.arg2_val = &fakeTemperatureInteger;
    dht11_get_fake.arg3_val = &fakeTemperatureDecimal;

    // Call the function to be tested
    get_dht11_sensor_data();

    // Check the expected behavior
    TEST_ASSERT_EQUAL(DHT11_OK, dht11_get_fake.return_val);
    TEST_ASSERT_EQUAL_UINT8(fakeHumidityInteger, humidity_integer);
    TEST_ASSERT_EQUAL_UINT8(fakeHumidityDecimal, humidity_decimal);
    TEST_ASSERT_EQUAL_UINT8(fakeTemperatureInteger, temperature_integer);
    TEST_ASSERT_EQUAL_UINT8(fakeTemperatureDecimal, temperature_decimal);
}

void testGetDHT11SensorData_Fail(void) {
    // Set the return value for the fake dht11_get function
    dht11_get_fake.return_val = DHT11_FAIL;

    // Call the function to be tested
    get_dht11_sensor_data();

    // Check the expected behavior
    TEST_ASSERT_EQUAL(DHT11_FAIL, dht11_get_fake.return_val);
    TEST_ASSERT_EQUAL_INT(-99, humidity_integer);
    TEST_ASSERT_EQUAL_INT(-99, humidity_decimal);
    TEST_ASSERT_EQUAL_INT(-99, temperature_integer);
    TEST_ASSERT_EQUAL_INT(-99, temperature_decimal);
}

// Add more test functions as needed

// Entry point for running the tests
int main(void) {
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(testGetDHT11SensorData_Success);
    RUN_TEST(testGetDHT11SensorData_Fail);
    // Add more RUN_TEST calls for other test functions

    UNITY_END();

    return 0;
}

#endif