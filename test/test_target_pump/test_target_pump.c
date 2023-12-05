#include "pump.h"
#include "unity.h"

uint8_t DDRH;   // Data Direction Register H
uint8_t PORTH;  // Port H

void setUp(void) {
    // Initialize mock hardware registers to a known state
    DDRH = 0x00;   // Set DDRH to 0x00 initially
    PORTH = 0xFF;  // Set PORTH to all high initially
}

void tearDown(void) {
    // Reset mock hardware registers after each test (if needed)

    DDRH = 0x00;
    PORTH = 0xFF;
}

void test_pump_init(void) {
    // Call the pump initialization function
    pump_init();

    // Check if DDRH bit 6 is set (should be an output)
    TEST_ASSERT_TRUE((DDRH & (1 << 6)) != 0);

    // Check if PORTH bit 6 is set (should be high - turned off, active low)
    TEST_ASSERT_TRUE((PORTH & (1 << 6)) != 0);
}

void test_pump_turnOn(void) {
    // Call the pump turnOn function
    pump_turnOn();

    // Check if PORTH bit 6 is cleared (should be low - turned on)
    TEST_ASSERT_TRUE((PORTH & (1 << 6)) == 0);
}

void test_pump_turnOff(void) {
    // Call the pump turnOff function
    pump_turnOff();

    // Check if PORTH bit 6 is set (should be high - turned off, active low)
    TEST_ASSERT_TRUE((PORTH & (1 << 6)) != 0);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_pump_init);
    RUN_TEST(test_pump_turnOn);
    RUN_TEST(test_pump_turnOff);

    return UNITY_END();
}
