#include "pump.h"
#include "includes.h"
#include "buttons.h"
#include "display.h"
#include "pump_controller.h"

extern int run_pump;

void pump_run_timeout(int miliseconds)
{
    pump_turnOn();
    #ifndef WINDOWS_TEST
    _delay_ms(miliseconds);
    #endif
    pump_turnOff();
}

void pump_run()
{
    pump_run_timeout(3000);
}

void pump_stop()
{
    pump_turnOff();
}

void pump_run_1_second()
{
    pump_run_timeout(1000);
}

void button_1_check()
{
  if (buttons_1_pressed() == 1)
  {
    run_pump = 1;
  }
}

void check_pump_run()
{
  if (run_pump == 1)
  {
    pump_run();
    run_pump = 0;
  }
}
