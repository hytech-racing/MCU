#include <SysClock.h>

// Constructor
SysClock::SysClock()
{
    for (int i = 0; i < static_cast<int>(TriggerIndices_e::NUM_TRIGGERS); i++)
    {
        triggerTimes[i] = 0;
    }
}

/*
    Get latest tick from sys clock
*/
SysTick_s SysClock::tick(unsigned long sysMicros)
{
    SysTick_s tickReturn = {
        .millis = sysMicros / 1000,
        .micros = sysMicros,
        .triggers = {
            .trigger1000    = sysMicros >= triggerTimes[static_cast<int>(TriggerIndices_e::TRIG_1000)],
            .trigger500     = sysMicros >= triggerTimes[static_cast<int>(TriggerIndices_e::TRIG_500)],
            .trigger100     = sysMicros >= triggerTimes[static_cast<int>(TriggerIndices_e::TRIG_100)],
            .trigger50      = sysMicros >= triggerTimes[static_cast<int>(TriggerIndices_e::TRIG_50)],
            .trigger10      = sysMicros >= triggerTimes[static_cast<int>(TriggerIndices_e::TRIG_10)],
            .trigger5       = sysMicros >= triggerTimes[static_cast<int>(TriggerIndices_e::TRIG_5)],
            .trigger1       = sysMicros >= triggerTimes[static_cast<int>(TriggerIndices_e::TRIG_1)]
        }
    };

    // Recalculate trigger times
    if (tickReturn.triggers.trigger1000)
        triggerTimes[static_cast<int>(TriggerIndices_e::TRIG_1000)] += 1'000;
    if (tickReturn.triggers.trigger500)
        triggerTimes[static_cast<int>(TriggerIndices_e::TRIG_500)] += 2'000;
    if (tickReturn.triggers.trigger100)
        triggerTimes[static_cast<int>(TriggerIndices_e::TRIG_100)] += 10'000;
    if (tickReturn.triggers.trigger50)
        triggerTimes[static_cast<int>(TriggerIndices_e::TRIG_50)] += 20'000;
    if (tickReturn.triggers.trigger10)
        triggerTimes[static_cast<int>(TriggerIndices_e::TRIG_10)] += 100'000;
    if (tickReturn.triggers.trigger5)
        triggerTimes[static_cast<int>(TriggerIndices_e::TRIG_5)] += 200'000;
    if (tickReturn.triggers.trigger1)
        triggerTimes[static_cast<int>(TriggerIndices_e::TRIG_1)] += 1'000'000;

    return tickReturn;
}