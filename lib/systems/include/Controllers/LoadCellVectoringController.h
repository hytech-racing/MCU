#ifndef LOADCELLVECTORINGCONTROLLER
#define LOADCELLVECTORINGCONTROLLER

#include "BaseController.h"
class TorqueControllerLoadCellVectoring : public virtual Controller
{
private:
    float frontTorqueScale_ = 1.0;
    float rearTorqueScale_ = 1.0;
    float frontRegenTorqueScale_ = 1.0;
    float rearRegenTorqueScale_ = 1.0;
    
    TorqueControllerOutput_s writeout_;
    /*
    FIR filter designed with
    http://t-filter.appspot.com

    sampling frequency: 100 Hz

    * 0 Hz - 10 Hz
    gain = 1
    desired ripple = 5 dB
    actual ripple = 1.7659949026015025 dB

    * 40 Hz - 50 Hz
    gain = 0
    desired attenuation = -40 dB
    actual attenuation = -47.34009380570117 dB
    */
    const static int numFIRTaps_ = 5;
    float FIRTaps_[numFIRTaps_] = {
        0.07022690881526232,
        0.27638313122745306,
        0.408090001549378,
        0.27638313122745306,
        0.07022690881526232};
    int FIRCircBufferHead = 0; // index of the latest sample in the raw buffer
    float loadCellForcesRaw_[4][numFIRTaps_] = {};
    float loadCellForcesFiltered_[4] = {};
    // Some checks that can disable the controller
    const int errorCountThreshold_ = 25;
    int loadCellsErrorCounter_[4] = {};
    bool FIRSaturated_ = false;
    bool ready_ = false;

public:
    /// @brief load cell TC with tunable F/R torque balance. Accel torque balance can be tuned independently of regen torque balance
    /// @param writeout the reference to the torque controller output being sent that contains the drivetrain command
    /// @param rearTorqueScale 0 to 2 scale on forward torque to rear wheels. 0 = FWD, 1 = Balanced, 2 = RWD
    /// @param regenTorqueScale same as rearTorqueScale but applies to regen torque split. 0 = All regen torque on the front, 1 = 50/50, 2 = all regen torque on the rear
    TorqueControllerLoadCellVectoring(float rearTorqueScale, float regenTorqueScale)
        : frontTorqueScale_(2.0 - rearTorqueScale),
          rearTorqueScale_(rearTorqueScale),
          frontRegenTorqueScale_(2.0 - regenTorqueScale),
          rearRegenTorqueScale_(regenTorqueScale)
    {
        writeout_.command = BaseControllerParams::TC_COMMAND_NO_TORQUE;
        writeout_.ready = false;
    }
    /// @brief default contructor with balanced dfault values: rearTorqueScale = 1.0, regenTorqueScale = 1.0
    TorqueControllerLoadCellVectoring() : TorqueControllerLoadCellVectoring(1.0, 1.0) {}

    /// @brief Calculates speed set point based on normal force applied to wheels individually
    /// @param SysTick_s &tick 
    /// @param PedalsSystemData_s &pedalsData 
    /// @param LoadCellInterfaceOutput_s &loadCellData 
    void tick(
        const SysTick_s &tick,
        const PedalsSystemData_s &pedalsData,
        const LoadCellInterfaceOutput_s &loadCellData);
    /// @brief ticks controller
    /// @param SharedCarState_s &state 
    /// @return TorqueControllerOutput_s
    TorqueControllerOutput_s evaluate(const SharedCarState_s &state) override;
};

#endif