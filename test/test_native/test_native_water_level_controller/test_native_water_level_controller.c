//Fully working testing class - use as a template

#include "../../fff.h"
#include <unity.h>
#include "hc_sr04.h"
#include "water_level_controller.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(hc_sr04_init);
FAKE_VALUE_FUNC(uint16_t, hc_sr04_takeMeasurement);

void setUp(void) {

    RESET_FAKE(hc_sr04_init);
    RESET_FAKE(hc_sr04_takeMeasurement);
}

void tearDown(void) {

}

void test_get_formatted_water_level_reading() {
    char buffer[128];

    hc_sr04_takeMeasurement_fake.return_val = 50;
    get_formatted_water_level_reading(buffer);

    TEST_ASSERT_EQUAL_STRING("\"TankLevel\": 50", buffer);
}

void test_get_water_level_reading() {

    hc_sr04_takeMeasurement_fake.return_val = 80;
    uint16_t result = get_water_level_reading();

    TEST_ASSERT_EQUAL_UINT16(80, result);
}

int main(void) {

    UNITY_BEGIN();

    RUN_TEST(test_get_formatted_water_level_reading);
    RUN_TEST(test_get_water_level_reading);

    return UNITY_END();
}
