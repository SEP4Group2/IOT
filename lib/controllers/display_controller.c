#include "display.h"
#include "includes.h"

const void writeToDisplay(uint8_t *receiveParameter)
{
    int part1, part2, part3, part4;
    char message[50];
    sprintf(message, "\nReceived: message from ESP32 is: %02d \n", receiveParameter);

    pc_comm_send_string_blocking(message);
    int totalNumber = *receiveParameter;

    // Truncate and store each 2-digit part
    part4 = totalNumber % 100;
    totalNumber /= 100;

    part3 = totalNumber % 100;
    totalNumber /= 100;

    part2 = totalNumber % 100;
    totalNumber /= 100;

    part1 = totalNumber; // The remaining part is stored in part1

    display_setValues(part1, part2, part3, part4);
};