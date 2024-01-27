#include <SysClock.h>

// Constructor
SysClock::SysClock()
{

}

SysTick_s SysClock::tick(unsigned long sysMicros)
{
    SysTick_s tickReturn = {
        .millis = sysMicros / 1000,
        .micros = sysMicros,
        .triggers = {
            .trigger1000    = sysMicros > triggerTimes[TRIG_1000],
            .trigger500     = sysMicros > triggerTimes[TRIG_500],
            .trigger100     = sysMicros > triggerTimes[TRIG_100],
            .trigger50      = sysMicros > triggerTimes[TRIG_50],
            .trigger10      = sysMicros > triggerTimes[TRIG_10],
            .trigger5       = sysMicros > triggerTimes[TRIG_5],
            .trigger1       = sysMicros > triggerTimes[TRIG_1]
        }
    };

    // Recalculate trigger times
    if (tickReturn.triggers.trigger1000)
        triggerTimes[TRIG_1000] += 1'000;
    if (tickReturn.triggers.trigger500)
        triggerTimes[TRIG_500] += 2'000;
    if (tickReturn.triggers.trigger100)
        triggerTimes[TRIG_100] += 10'000;
    if (tickReturn.triggers.trigger50)
        triggerTimes[TRIG_50] += 20'000;
    if (tickReturn.triggers.trigger10)
        triggerTimes[TRIG_10] += 100'000;
    if (tickReturn.triggers.trigger5)
        triggerTimes[TRIG_5] += 200'000;
    if (tickReturn.triggers.trigger1)
        triggerTimes[TRIG_1] += 1'000'000;
}