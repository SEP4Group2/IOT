#include "../../fff.h"
#include <unity.h>
#include "pump_controller.h" 
#include "buttons.h" 

DEFINE_FFF_GLOBALS;

// Mock functions for pump controller
FAKE_VOID_FUNC(pump_turnOn);
FAKE_VOID_FUNC(pump_turnOff);

// Mock function for button press
FAKE_VALUE_FUNC(uint8_t, buttons_1_pressed);

int run_pump;

void setUp(void) 
{
}

void tearDown(void) 
{
}

// Test case for button_1_check
void test_button_1_check() {
    // Arrange
    buttons_1_pressed_fake.return_val = 1; // Simulate button press
    run_pump = 0; // Initialize to a known state
    
    // Act
    button_1_check();
    
    // Assert
    TEST_ASSERT_EQUAL_INT(1, run_pump); // Check if run_pump is set to 1 after button press
}

// Test case for check_pump_run
void test_check_pump_run() {
    // Arrange
    run_pump = 1; // Simulate run_pump being set
    
    // Act
    check_pump_run();
    
    // Assert
    TEST_ASSERT_EQUAL_INT(0, run_pump); // Check if run_pump is reset after pump_run is executed
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_button_1_check);
    RUN_TEST(test_check_pump_run);

    return UNITY_END();
}