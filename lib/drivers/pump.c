#include "pump.h"
#include "includes.h"

void pump_init(void)
{
    DDRH |= (1 << 6);
    PORTH |= (1 << 6); // turnOff (Active Low)
}

void pump_turnOn()
{
    PORTH &= ~(1 << 6);
}

void pump_turnOff()
{
    PORTH |= ((1 << 6));
}

// void pump_run_timeout(int miliseconds)
// {
//     pump_turnOn();
//     _delay_ms(miliseconds);
//     pump_turnOff();
// }