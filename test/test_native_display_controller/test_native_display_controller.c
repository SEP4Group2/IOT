#include "../fff.h"
#include "unity.h"
#include "display_controller.h"
#include "stdlib.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(writeToDisplay, char*);

// Expected variables to set the display to
int expected_part1, expected_part2, expected_part3, expected_part4;

// Mock writeToDisplay from display_controller.h
void mock_writeToDisplay(char *receiveParameter) {
    char *endptr;
    long integerValue = strtol(receiveParameter, &endptr, 10);

    int part1, part2, part3, part4;

    // Simulate the calculation of part1, part2, part3, part4
    long totalNumber = integerValue;
    part4 = totalNumber % 100;
    totalNumber /= 100;
    part3 = totalNumber % 100;
    totalNumber /= 100;
    part2 = totalNumber % 100;
    totalNumber /= 100;
    part1 = totalNumber;

    TEST_ASSERT_EQUAL_INT(expected_part1, part1);
    TEST_ASSERT_EQUAL_INT(expected_part2, part2);
    TEST_ASSERT_EQUAL_INT(expected_part3, part3);
    TEST_ASSERT_EQUAL_INT(expected_part4, part4);
}

void setUp(void) {
    // Just in case
    expected_part1 = 0;
    expected_part2 = 0;
    expected_part3 = 0;
    expected_part4 = 0;
}

void tearDown(void) {
 
    expected_part1 = 0;
    expected_part2 = 0;
    expected_part3 = 0;
    expected_part4 = 0;
}

void test_writeToDisplay() {
    char testInput[] = "12345678";

    expected_part1 = 12;
    expected_part2 = 34;
    expected_part3 = 56;
    expected_part4 = 78;

    writeToDisplay_fake.custom_fake = mock_writeToDisplay;

    writeToDisplay(testInput);
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_writeToDisplay);

    UNITY_END();
}
