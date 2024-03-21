#include "TorqueControllers.h"
#include "Utility.h"
#include <algorithm>
#include "PhysicalParameters.h"

// TorqueControllerSimple

void TorqueControllerSimple::tick(const SysTick_s &tick, const PedalsSystemData_s &pedalsData, float torqueLimit)
{

    // Calculate torque commands at 100hz
    if (tick.triggers.trigger100)
    {
        // Both pedals are not pressed and no implausibility has been detected
        // accelRequest goes between 1.0 and -1.0
        float accelRequest = pedalsData.accelPercent - pedalsData.regenPercent;
        float torqueRequest;

        if (accelRequest >= 0.0)
        {
            // Positive torque request
            torqueRequest = accelRequest * AMK_MAX_TORQUE;

            // writeout_.command.speeds_rpm[FL] = accelRequest * AMK_MAX_RPM;
            // writeout_.command.speeds_rpm[FR] = accelRequest * AMK_MAX_RPM;
            // writeout_.command.speeds_rpm[RL] = accelRequest * AMK_MAX_RPM;
            // writeout_.command.speeds_rpm[RR] = accelRequest * AMK_MAX_RPM;
            writeout_.command.speeds_rpm[FL] = AMK_MAX_RPM;
            writeout_.command.speeds_rpm[FR] = AMK_MAX_RPM;
            writeout_.command.speeds_rpm[RL] = AMK_MAX_RPM;
            writeout_.command.speeds_rpm[RR] = AMK_MAX_RPM;

            writeout_.command.torqueSetpoints[FL] = torqueRequest * frontTorqueScale_;
            writeout_.command.torqueSetpoints[FR] = torqueRequest * frontTorqueScale_;
            writeout_.command.torqueSetpoints[RL] = torqueRequest * rearTorqueScale_;
            writeout_.command.torqueSetpoints[RR] = torqueRequest * rearTorqueScale_;
        }
        else
        {
            // Negative torque request
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

        // Apply the torque limit
        TCPosTorqueLimit(writeout_.command, torqueLimit);
    }
}

// TorqueControllerLoadCellVectoring

void TorqueControllerLoadCellVectoring::tick(
    const SysTick_s &tick,
    const PedalsSystemData_s &pedalsData,
    float torqueLimit,
    const AnalogConversion_s &flLoadCellData,
    const AnalogConversion_s &frLoadCellData,
    const AnalogConversion_s &rlLoadCellData,
    const AnalogConversion_s &rrLoadCellData)
{
    // Calculate torque commands at 100hz
    if (tick.triggers.trigger100)
    {
        // Apply FIR filter to load cell data
        loadCellForcesRaw_[0][FIRCircBufferHead] = flLoadCellData.conversion;
        loadCellForcesRaw_[1][FIRCircBufferHead] = frLoadCellData.conversion;
        loadCellForcesRaw_[2][FIRCircBufferHead] = rlLoadCellData.conversion;
        loadCellForcesRaw_[3][FIRCircBufferHead] = rrLoadCellData.conversion;

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
        loadCellsErrorCounter_[0] = flLoadCellData.raw != 4095 && flLoadCellData.status != AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED ? 0 : loadCellsErrorCounter_[0] + 1;
        loadCellsErrorCounter_[1] = frLoadCellData.raw != 4095 && frLoadCellData.status != AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED ? 0 : loadCellsErrorCounter_[1] + 1;
        loadCellsErrorCounter_[2] = rlLoadCellData.raw != 4095 && rlLoadCellData.status != AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED ? 0 : loadCellsErrorCounter_[2] + 1;
        loadCellsErrorCounter_[3] = rrLoadCellData.raw != 4095 && rrLoadCellData.status != AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED ? 0 : loadCellsErrorCounter_[3] + 1;
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

                writeout_.command.torqueSetpoints[FL] = torqueRequest;
                writeout_.command.torqueSetpoints[FR] = torqueRequest;
                writeout_.command.torqueSetpoints[RL] = torqueRequest;
                writeout_.command.torqueSetpoints[RR] = torqueRequest;
            }

            // Apply the torque limit
            TCPosTorqueLimit(writeout_.command, torqueLimit);
        }
        else
        {
            writeout_.command = TC_COMMAND_NO_TORQUE;
        }
    }
}