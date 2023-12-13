#ifdef PUMP_TARGET_TEST

#include "pump.h"
#include "unity.h"
#include <avr/io.h> 

void setUp(void)
{

}

void tearDown(void)
{
    DDRH &= ~(1 << 6); 
    PORTH &= ~(1 << 6); 
}

void test_pump_init(void) {
 
    pump_init();

    TEST_ASSERT_TRUE((DDRH & (1 << 6)) != 0);

    TEST_ASSERT_TRUE((PORTH & (1 << 6)) == 0);
}

void test_pump_turnOn(void) {
    
    DDRH |= (1 << 6); 
    PORTH &= ~(1 << 6); 
    
    pump_turnOn();

    TEST_ASSERT_TRUE((PORTH & (1 << 6)) != 0);

    //Extra instruction because sometimes pump gets stuck on high
    PORTH &= ~(1 << 6); 
}

void test_pump_turnOff(void) {
    
    DDRH |= (1 << 6);   // Set DDRH bit 6
    PORTH |= (1 << 6);  // Set PORTH bit 6

    pump_turnOff();

    //Test if bit is cleared
    TEST_ASSERT_TRUE((PORTH & (1 << 6)) == 0);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_pump_init);
    RUN_TEST(test_pump_turnOn);
    RUN_TEST(test_pump_turnOff);

    return UNITY_END();
}

#endif
