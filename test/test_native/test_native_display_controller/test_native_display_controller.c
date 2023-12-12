#include "../../fff.h"
#include "unity.h"
#include "display_controller.h"
#include "display.h"
#include "stdlib.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(display_setValues, uint8_t, uint8_t, uint8_t, uint8_t)

void setUp(void) {

}

void tearDown(void) {
 
}

void display_test()
{
    writeToDisplay("12345678");

    TEST_ASSERT_EQUAL(display_setValues_fake.arg0_val, 12);
    TEST_ASSERT_EQUAL(display_setValues_fake.arg1_val, 34);
    TEST_ASSERT_EQUAL(display_setValues_fake.arg2_val, 56);
    TEST_ASSERT_EQUAL(display_setValues_fake.arg3_val, 78);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(display_test);

    UNITY_END();
}
