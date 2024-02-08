#ifndef __SYSCLK_H__
#define __SYSCLK_H__

struct TriggerBits_s
{
    bool trigger1000 : 1;
    bool trigger500 : 1;
    bool trigger100 : 1;
    bool trigger50 : 1;
    bool trigger10 : 1;
    bool trigger5 : 1;
    bool trigger1 : 1;
};

struct SysTick_s
{
    unsigned long millis;
    unsigned long micros;
    TriggerBits_s triggers;
};

class SysClock
{
private:
    enum class TriggerIndices_e
    {
        TRIG_1000 = 0,
        TRIG_500 = 1,
        TRIG_100 = 2,
        TRIG_50 = 3,
        TRIG_10 = 4,
        TRIG_5 = 5,
        TRIG_1 = 6,
        NUM_TRIGGERS = 7
    };

    unsigned long triggerTimes[static_cast<int>(TriggerIndices_e::NUM_TRIGGERS)];

public:
    SysClock();
    SysTick_s tick(unsigned long sysMicros);
};

#endif /* __SYSCLK_H__ */