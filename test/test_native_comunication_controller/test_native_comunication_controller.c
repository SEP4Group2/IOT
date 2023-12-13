#include "../fff.h"
#include "unity.h"
#include "wifi.h"
#include "communication_controller.h"

DEFINE_FFF_GLOBALS;

// Mocks
FAKE_VALUE_FUNC(char *, testWifiConnection, WIFI_ERROR_MESSAGE_t);

FAKE_VALUE_FUNC(char *, testTcpConnection, WIFI_ERROR_MESSAGE_t);

FAKE_VALUE_FUNC(int, is_data_acknowledged);

FAKE_VOID_FUNC(pump_run);
FAKE_VOID_FUNC(writeFloatToEEPROM, int);

int data_acknowledged;

// Reset the fakes before each test
void setUp(void)
{

    FFF_RESET_HISTORY();
}

void tearDown(void)
{
}

// Test cases go here

void test_WifiConnection_OK(void)
{

    RESET_FAKE(testWifiConnection);

    // Arrange
    WIFI_ERROR_MESSAGE_t errorcode = WIFI_OK;
    testWifiConnection_fake.return_val = "\nWifi connect OK";

    // Act
    char *result = testWifiConnection(errorcode);

    // Assert
    TEST_ASSERT_EQUAL_STRING("\nWifi connect OK", result);
    TEST_ASSERT_EQUAL(1, testWifiConnection_fake.call_count);
    TEST_ASSERT_EQUAL(WIFI_OK, testWifiConnection_fake.arg0_val);
}

void test_WifiConnection_Fail(void)
{

    RESET_FAKE(testWifiConnection);

    // Arrange
    WIFI_ERROR_MESSAGE_t errorcode = WIFI_FAIL;
    testWifiConnection_fake.return_val = "\nWifi connect FAIL";

    // Act
    char *result = testWifiConnection(errorcode);

    // Assert
    TEST_ASSERT_EQUAL_STRING("\nWifi connect FAIL", result);
    TEST_ASSERT_EQUAL(1, testWifiConnection_fake.call_count);
    TEST_ASSERT_EQUAL(WIFI_FAIL, testWifiConnection_fake.arg0_val);
}

void test_TcpConnection_OK(void)
{
    // Reset the fake before each test
    RESET_FAKE(testTcpConnection);

    // Arrange
    WIFI_ERROR_MESSAGE_t errorcode = WIFI_OK;
    testTcpConnection_fake.return_val = "\nTcp connect OK";

    // Act
    char *result = testTcpConnection(errorcode);

    // Assert
    TEST_ASSERT_EQUAL_STRING("\nTcp connect OK", result);
    TEST_ASSERT_EQUAL(1, testTcpConnection_fake.call_count);
    TEST_ASSERT_EQUAL(WIFI_OK, testTcpConnection_fake.arg0_val);
}

void test_TcpConnection_Fail(void)
{
    // Reset the fake before each test
    RESET_FAKE(testTcpConnection);

    // Arrange
    WIFI_ERROR_MESSAGE_t errorcode = WIFI_FAIL;
    testTcpConnection_fake.return_val = "\nTcp connect FAIL";

    // Act
    char *result = testTcpConnection(errorcode);

    // Assert
    TEST_ASSERT_EQUAL_STRING("\nTcp connect FAIL", result);
    TEST_ASSERT_EQUAL(1, testTcpConnection_fake.call_count);
    TEST_ASSERT_EQUAL(WIFI_FAIL, testTcpConnection_fake.arg0_val);
}

void test_DataNotAcknowledged(void)
{
    // Reset the fake before each test
    RESET_FAKE(is_data_acknowledged);

    // Arrange
    data_acknowledged = 0;
    is_data_acknowledged_fake.return_val = 0;

    // Act
    int result = is_data_acknowledged();

    // Assert
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, is_data_acknowledged_fake.call_count);
}

void test_DataAcknowledged(void)
{
    // Reset the fake before each test
    RESET_FAKE(is_data_acknowledged);

    // Arrange
    data_acknowledged = 1;
    is_data_acknowledged_fake.return_val = 1;

    // Act
    int result = is_data_acknowledged();

    // Assert
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(1, is_data_acknowledged_fake.call_count);
}

// Entry point for running the tests
int main(void)
{
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(test_WifiConnection_OK);
    RUN_TEST(test_WifiConnection_Fail);

    RUN_TEST(test_TcpConnection_OK);
    RUN_TEST(test_TcpConnection_Fail);

    RUN_TEST(test_DataNotAcknowledged);
    RUN_TEST(test_DataAcknowledged);

    UNITY_END();

    return 0;
}
