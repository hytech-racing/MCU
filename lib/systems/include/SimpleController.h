#ifndef SIMPLECONTROLLER
#define SIMPLECONTROLLER

#include "BaseController.h"



class TorqueControllerSimple : public Controller
{
private:
    TorqueControllerOutput_s writeout_;
    float frontTorqueScale_ = 1.0;
    float rearTorqueScale_ = 1.0;
    float frontRegenTorqueScale_ = 1.0;
    float rearRegenTorqueScale_ = 1.0;

public:
    /// @brief simple TC with tunable F/R torque balance. Accel torque balance can be tuned independently of regen torque balance
    /// @param writeout the reference to the torque controller output being sent that contains the drivetrain command
    /// @param rearTorqueScale 0 to 2 scale on forward torque to rear wheels. 0 = FWD, 1 = Balanced, 2 = RWD
    /// @param regenTorqueScale same as rearTorqueScale but applies to regen torque split. 0 = All regen torque on the front, 1 = 50/50, 2 = all regen torque on the rear
    TorqueControllerSimple(float rearTorqueScale, float regenTorqueScale)
        : frontTorqueScale_(2.0 - rearTorqueScale),
          rearTorqueScale_(rearTorqueScale),
          frontRegenTorqueScale_(2.0 - regenTorqueScale),
          rearRegenTorqueScale_(regenTorqueScale)
    {
        writeout_.command = BaseControllerParams::TC_COMMAND_NO_TORQUE;
        writeout_.ready = true;
    }

    void tick(const PedalsSystemData_s &pedalsData);
    TorqueControllerOutput_s evaluate(const SharedCarState_s &state) override;
};

#endif