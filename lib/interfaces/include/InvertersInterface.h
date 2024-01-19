#ifndef __INVERTERSINTERFACE_H__
#define __INVERTERSINTERFACE_H__

#define INV_FL 0
#define INV_FR 1
#define INV_RL 2
#define INV_RR 3

class InvertersInterface
{
private:
public:
    virtual void softReset();
    virtual void hardReset();
    virtual void clearFaults();
    virtual void enable();
    virtual void disable();
    virtual int* getStatuses();
    virtual float* getTorques();
    virtual float* getSpeeds();
    virtual float* getTorqueCurrents();
    virtual float* getMagnetizingCurrents();
    virtual void setPositiveTorqueLimits(float FLTorqueLim, float FRTorqueLim, float RLTorqueLim, float RRTorqueLim);
    virtual void setNegativeTorqueLimits(float FLTorqueLim, float FRTorqueLim, float RLTorqueLim, float RRTorqueLim);
    virtual void setSpeedTargets(float FLSpeed, float FRSpeed, float RLSpeed, float RRSpeed);
};

#endif /* __INVERTERSINTERFACE_H__ */