//Fully working testing class - use as a template

#include "../../fff.h"
#include <unity.h>
#include "uvsensor.h"
#include "uvsensor_controller.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(uvsensor_init);
FAKE_VALUE_FUNC(uint16_t, uvsensor_read);

void setUp(void) {
    RESET_FAKE(uvsensor_init);
    RESET_FAKE(uvsensor_read);
}

void tearDown(void) {
}

void test_get_formatted_uv_sensor_reading() {
    char buffer[128];

    uvsensor_read_fake.return_val = 60; 
    get_formatted_uv_sensor_reading(buffer);

    TEST_ASSERT_EQUAL_STRING("\\\"UVLight\\\": 60", buffer); 
}

void test_get_uv_sensor_reading() {
    uvsensor_read_fake.return_val = 80; 

    uint16_t result = get_uv_sensor_reading();

    TEST_ASSERT_EQUAL_UINT16(80, result); 
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_get_formatted_uv_sensor_reading);
    RUN_TEST(test_get_uv_sensor_reading);

    return UNITY_END();
}
