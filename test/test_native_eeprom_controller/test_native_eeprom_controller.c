/*#include "../../fff.h"
#include "unity.h"
#include "eeprom_controller.h"

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


// Mocking EEPROM functions
FAKE_VOID_FUNC(eeprom_write_block, const void*, void*, size_t);
FAKE_VALUE_FUNC(uint8_t, eeprom_read_block, const void*, void*, size_t);

#define EEPROM_FLOAT_START_ADDRESS 4090

void testWriteReadToEEPROM(void) {
    int data = 42;

    // Set the expected data value for read
    eeprom_read_block_fake.return_val = 1;
    eeprom_read_block_fake.arg0_val = &data;

    // Call the function to be tested
    writeFloatToEEPROM(data);

    // Check the expected behavior
    TEST_ASSERT_EQUAL(1, eeprom_write_block_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&data, eeprom_write_block_fake.arg0_val);
    TEST_ASSERT_EQUAL_PTR((void *)EEPROM_FLOAT_START_ADDRESS, eeprom_write_block_fake.arg1_val);
    TEST_ASSERT_EQUAL(4, eeprom_write_block_fake.arg2_val);

    // Now, test the read function
    int result = readFloatFromEEPROM();
    TEST_ASSERT_EQUAL(1, eeprom_read_block_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&data, eeprom_read_block_fake.arg0_val);
    TEST_ASSERT_EQUAL_PTR((const void *)EEPROM_FLOAT_START_ADDRESS, eeprom_read_block_fake.arg1_val);
    TEST_ASSERT_EQUAL(4, eeprom_read_block_fake.arg2_val);
    TEST_ASSERT_EQUAL(42, result);
}

// Add more test functions as needed

int main(void) {
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(testWriteReadToEEPROM);

    UNITY_END();

    return 0;
}
*/