#include "LoadCellVectoringController.h"


void TorqueControllerLoadCellVectoring::tick(
    const SysTick_s &tick,
    const PedalsSystemData_s &pedalsData,
    const LoadCellInterfaceOutput_s &loadCellData
)
{
    // Calculate torque commands at 100hz
    if (tick.triggers.trigger100)
    {
        // Apply FIR filter to load cell data
        loadCellForcesRaw_[0][FIRCircBufferHead] = loadCellData.loadCellForcesFiltered.FL;
        loadCellForcesRaw_[1][FIRCircBufferHead] = loadCellData.loadCellForcesFiltered.FR;
        loadCellForcesRaw_[2][FIRCircBufferHead] = loadCellData.loadCellForcesFiltered.RL;
        loadCellForcesRaw_[3][FIRCircBufferHead] = loadCellData.loadCellForcesFiltered.RR;

        for (int i = 0; i < 4; i++)
        {
            loadCellForcesFiltered_[i] = 0.0f;
            for (int FIROffset = 0; FIROffset < numFIRTaps_; FIROffset++)
            {
                int index = (FIRCircBufferHead + FIROffset) % numFIRTaps_;
                loadCellForcesFiltered_[i] += loadCellForcesRaw_[i][index] * FIRTaps_[FIROffset];
            }
        }
        FIRCircBufferHead = (FIRCircBufferHead + 1) % numFIRTaps_;
        if (FIRCircBufferHead == numFIRTaps_ - 1)
            FIRSaturated_ = true;

        // Do sanity checks on raw data
        loadCellsErrorCounter_[0] = loadCellData.loadCellConversions.FL.raw != 4095 && loadCellData.loadCellConversions.FL.status != AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED ? 0 : loadCellsErrorCounter_[0] + 1;
        loadCellsErrorCounter_[1] = loadCellData.loadCellConversions.FR.raw != 4095 && loadCellData.loadCellConversions.FR.status != AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED ? 0 : loadCellsErrorCounter_[1] + 1;
        loadCellsErrorCounter_[2] = loadCellData.loadCellConversions.RL.raw != 4095 && loadCellData.loadCellConversions.RL.status != AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED ? 0 : loadCellsErrorCounter_[2] + 1;
        loadCellsErrorCounter_[3] = loadCellData.loadCellConversions.RR.raw != 4095 && loadCellData.loadCellConversions.RR.status != AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED ? 0 : loadCellsErrorCounter_[3] + 1;
        ready_ = FIRSaturated_ && loadCellsErrorCounter_[0] < errorCountThreshold_ && loadCellsErrorCounter_[1] < errorCountThreshold_ && loadCellsErrorCounter_[2] < errorCountThreshold_ && loadCellsErrorCounter_[3] < errorCountThreshold_;

        writeout_.ready = ready_;

        if (ready_)
        {
            // Calculate total normal force
            float sumNormalForce = 0.0f;
            for (int i = 0; i < 4; i++)
            {
                sumNormalForce += loadCellForcesFiltered_[i];
            }

            // Both pedals are not pressed and no implausibility has been detected
            // accelRequest goes between 1.0 and -1.0
            float accelRequest = pedalsData.accelPercent - pedalsData.regenPercent;
            float torquePool;
            float torqueRequest;

            if (accelRequest >= 0.0)
            {
                // Positive torque request
                // NOTE: using "torquePool" here instead of torqueRequest for legibility
                torquePool = accelRequest * AMK_MAX_TORQUE * 4;

                writeout_.command.speeds_rpm[FL] = AMK_MAX_RPM;
                writeout_.command.speeds_rpm[FR] = AMK_MAX_RPM;
                writeout_.command.speeds_rpm[RL] = AMK_MAX_RPM;
                writeout_.command.speeds_rpm[RR] = AMK_MAX_RPM;

                writeout_.command.torqueSetpoints[FL] = torquePool * frontTorqueScale_ * loadCellForcesFiltered_[0] / sumNormalForce;
                writeout_.command.torqueSetpoints[FR] = torquePool * frontTorqueScale_ * loadCellForcesFiltered_[1] / sumNormalForce;
                writeout_.command.torqueSetpoints[RL] = torquePool * rearTorqueScale_ * loadCellForcesFiltered_[2] / sumNormalForce;
                writeout_.command.torqueSetpoints[RR] = torquePool * rearTorqueScale_ * loadCellForcesFiltered_[3] / sumNormalForce;
            }
            else
            {
                // Negative torque request
                // No load cell vectoring on regen
                torqueRequest = MAX_REGEN_TORQUE * accelRequest * -1.0;

                writeout_.command.speeds_rpm[FL] = 0.0;
                writeout_.command.speeds_rpm[FR] = 0.0;
                writeout_.command.speeds_rpm[RL] = 0.0;
                writeout_.command.speeds_rpm[RR] = 0.0;

                writeout_.command.torqueSetpoints[FL] = torqueRequest * frontRegenTorqueScale_;
                writeout_.command.torqueSetpoints[FR] = torqueRequest * frontRegenTorqueScale_;
                writeout_.command.torqueSetpoints[RL] = torqueRequest * rearRegenTorqueScale_;
                writeout_.command.torqueSetpoints[RR] = torqueRequest * rearRegenTorqueScale_;
            }
        }
        else
        {
            writeout_.command = TC_COMMAND_NO_TORQUE;
        }
    }
}

TorqueControllerOutput_s TorqueControllerLoadCellVectoring::evaluate(const car_state &state)
{
    tick(state.systick, state.pedals_data, state.loadcell_data);
    return writeout_;
}