#include "pump.h"
#include "includes.h"
#include "buttons.h"
#include "display.h"


void pump_run_timeout(int miliseconds)
{
    pump_turnOn();
    _delay_ms(miliseconds);
    pump_turnOff();
}

void pump_run()
{
    pump_run_timeout(3000);
    pc_comm_send_string_blocking("Pump turned on\n");

}

void pump_stop()
{
    pump_turnOff();
    pc_comm_send_string_blocking("Pump turned off\n");
}

void pump_run_1_second_button()
{
    pump_run_timeout(1000);
    pc_comm_send_string_blocking("Pump turned on for 1 second\n");
}

void *button_1_check()
{
  if (buttons_1_pressed() == 1)
  {
    display_setValues(13, 14, 10, 13);
    pump_run_timeout(2000);
  }
}
