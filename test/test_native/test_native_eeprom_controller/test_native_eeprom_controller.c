#include "mock_eeprom_controller.h"
#include "unity.h"

void setUp(void) 
{

}

void tearDown(void) 
{

}

//Since we can't use avr/eeprom.h then the functions have to be mocked

static int mock_eeprom_data = 0;

void mock_writeFloatToEEPROM(int data) {
    mock_eeprom_data = data;
}

int mock_readFloatFromEEPROM() {
    return mock_eeprom_data;
}

//End of mocks

void testWriteReadToEEPROM(void) {
  
    int data = 42;

    mock_writeFloatToEEPROM(data);

    int result = mock_readFloatFromEEPROM();

    TEST_ASSERT_EQUAL_INT(data, result);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(testWriteReadToEEPROM);

    return UNITY_END();
}
