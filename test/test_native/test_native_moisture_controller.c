//Fully working testing class - use as a template

#include "../../fff.h"
#include <unity.h>
#include "moisture.h"
#include "moisture_controller.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(moisture_init);
FAKE_VALUE_FUNC(uint16_t, moisture_read);

void setUp(void) {
    RESET_FAKE(moisture_init);
    RESET_FAKE(moisture_read);
}

void tearDown(void) {
}

void test_get_formatted_moisture_reading() {
    char buffer[128];

    moisture_read_fake.return_val = 60; 
    get_formatted_moisture_reading(buffer);

    TEST_ASSERT_EQUAL_STRING("\\\"Moisture\\\": 60", buffer); 
}

void test_get_moisture_reading() {
    moisture_read_fake.return_val = 80; 

    uint16_t result = get_moisture_reading();

    TEST_ASSERT_EQUAL_UINT16(80, result); 
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_get_formatted_moisture_reading);
    RUN_TEST(test_get_moisture_reading);

    return UNITY_END();
}
