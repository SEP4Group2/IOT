#include "../../fff.h"
#include "eeprom_controller.h"
#include "avr/eeprom.h"
#include <string.h>
#include <stdio.h>
#include <unity.h>

// Define the start address of the EEPROM
#define EEPROM_FLOAT_START_ADDRESS 4090

DEFINE_FFF_GLOBALS;

// Declare FFF-defined fake functions for eeprom.h
FAKE_VOID_FUNC(eeprom_write_block, const void *, void *, size_t);
FAKE_VOID_FUNC(eeprom_read_block, void *, const void *, size_t);

void setUp() {
    // Initialize FFF and reset fake functions before each test
    FFF_RESET_HISTORY();
    RESET_FAKE(eeprom_write_block);
    RESET_FAKE(eeprom_read_block);
}

void tearDown() {
    // Clean up after each test if needed
}

void test_writeFloatToEEPROM() {
    int data = 42;

    // Define a pointer to the EEPROM start address
    const void *expected_address = (const void *)EEPROM_FLOAT_START_ADDRESS;

    // Simulate EEPROM write
    writeFloatToEEPROM(data);

    // Ensure eeprom_write_block was called with correct parameters
    TEST_ASSERT_EQUAL_PTR(&data, eeprom_write_block_fake.arg0_val);
    TEST_ASSERT_EQUAL_PTR(expected_address, eeprom_write_block_fake.arg1_val);
    TEST_ASSERT_EQUAL_INT(4, eeprom_write_block_fake.arg2_val);
}

void test_readFloatFromEEPROM() {
    int expected_data = 42;
    int data;

    // Set up fake return data
    eeprom_read_block_fake.arg0_val = &expected_data;

    // Define a pointer to the EEPROM start address
    const void *expected_address = (const void *)EEPROM_FLOAT_START_ADDRESS;

    // Simulate EEPROM read
    data = readFloatFromEEPROM();

    // Ensure eeprom_read_block was called with correct parameters
    TEST_ASSERT_EQUAL_PTR(&data, eeprom_read_block_fake.arg0_val);
    TEST_ASSERT_EQUAL_PTR(expected_address, eeprom_read_block_fake.arg1_val); // Compare pointers
    TEST_ASSERT_EQUAL_INT(4, eeprom_read_block_fake.arg2_val);

    // Ensure the returned data is correct
    TEST_ASSERT_EQUAL_INT(expected_data, data);
}


int main() {
    UNITY_BEGIN();
    RUN_TEST(test_writeFloatToEEPROM);
    RUN_TEST(test_readFloatFromEEPROM);
    return UNITY_END();
}
