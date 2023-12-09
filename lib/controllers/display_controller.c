#include "display.h"
#include "includes.h"
#include "display_controller.h"

const void writeToDisplay(char *receiveParameter)
{
    char *endptr;

    long integerValue = strtol(receiveParameter, &endptr, 10);

    int part1, part2, part3, part4;
    char message[128];
    sprintf(message, "Writing to display>>: %s\n", integerValue);
    pc_comm_send_string_blocking(message);
    long totalNumber = integerValue;

    // Truncate and store each 2-digit part
    part4 = totalNumber % 100;
    totalNumber /= 100;

    part3 = totalNumber % 100;
    totalNumber /= 100;

    part2 = totalNumber % 100;
    totalNumber /= 100;

    part1 = totalNumber; // The remaining part is stored in part1

    display_setValues(part1, part2, part3, part4);
    // pc_comm_send_string_blocking("\n SS");
    pc_comm_send_string_blocking(part1);
    pc_comm_send_string_blocking(part2);
    pc_comm_send_string_blocking(part3);
    pc_comm_send_string_blocking(part4);
};