#ifdef PUMP_TARGET_TEST

#include "pump.h"
#include "unity.h"
#include <avr/io.h> 

void setUp(void)
{
    // Initialize the fakes
}

void tearDown(void)
{
    // Clean up after the test
}

void test_pump_init(void) {
    // Call the pump initialization function
    // pump_init();

    // Check if DDRH bit 6 is set (should be an output)
    TEST_ASSERT_TRUE((DDRH & (1 << 6)) != 0);

    // Check if PORTH bit 6 is set (should be high - turned off, active low)
    TEST_ASSERT_TRUE((PORTH & (1 << 6)) != 0);
}

void test_pump_turnOn(void) {
    // Initialize DDRH and PORTH to known states before the test
    // DDRH |= (1 << 6);   // Set DDRH bit 6 as an output
    // PORTH |= (1 << 6);  // Set PORTH bit 6 initially (simulate off state)

    // Call the pump turnOn function
    // pump_turnOn();

    // Check if PORTH bit 6 is cleared (should be low - turned on)
    TEST_ASSERT_TRUE((PORTH & (1 << 6)) == 0);
}

void test_pump_turnOff(void) {
    // Initialize DDRH and PORTH to known states before the test
    // DDRH |= (1 << 6);   // Set DDRH bit 6 as an output
    // PORTH &= ~(1 << 6); // Clear PORTH bit 6 initially (simulate on state)

    // Call the pump turnOff function
    // pump_turnOff();

    // Check if PORTH bit 6 is set (should be high - turned off, active low)
    TEST_ASSERT_TRUE((PORTH & (1 << 6)) != 0);
}

int main(void) {
    UNITY_BEGIN();

    // RUN_TEST(test_pump_init);
    // RUN_TEST(test_pump_turnOn);
    RUN_TEST(test_pump_turnOff);

    return UNITY_END();
}

#endif
