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

void TorqueControllerSimpleLaunch::tick(
    const SysTick_s &tick,
    const PedalsSystemData_s &pedalsData,
    const float wheel_rpms[])
{

    int16_t brake_torque_req = pedalsData.regenPercent * MAX_REGEN_TORQUE;

    float max_speed = 0;
    for(int i = 0; i < 4; i++){
        max_speed = std::max(max_speed, abs(wheel_rpms[i]));
    }

    writeout_.ready = true;

    switch(launch_state){
        case LaunchStates_e::LAUNCH_NOT_READY:
            // set torques and speed to 0
            writeout_.command.speeds_rpm[FL] = 0.0;
            writeout_.command.speeds_rpm[FR] = 0.0;
            writeout_.command.speeds_rpm[RL] = 0.0;
            writeout_.command.speeds_rpm[RR] = 0.0;

            writeout_.command.torqueSetpoints[FL] = brake_torque_req;
            writeout_.command.torqueSetpoints[FR] = brake_torque_req;
            writeout_.command.torqueSetpoints[RL] = brake_torque_req;
            writeout_.command.torqueSetpoints[RR] = brake_torque_req;

            //init launch vars
            launch_speed_target = 0;
            time_of_launch = tick.millis;
            // check speed is 0 and pedals not pressed
            if((pedalsData.accelPercent < launch_ready_accel_threshold)
               && (pedalsData.brakePercent < launch_ready_brake_threshold)
               && (max_speed < launch_ready_speed_threshold))
            {
                launch_state = LaunchStates_e::LAUNCH_READY;
            }

            break;
        case LaunchStates_e::LAUNCH_READY:
            // set torques and speed to 0
            writeout_.command.speeds_rpm[FL] = 0.0;
            writeout_.command.speeds_rpm[FR] = 0.0;
            writeout_.command.speeds_rpm[RL] = 0.0;
            writeout_.command.speeds_rpm[RR] = 0.0;

            writeout_.command.torqueSetpoints[FL] = brake_torque_req;
            writeout_.command.torqueSetpoints[FR] = brake_torque_req;
            writeout_.command.torqueSetpoints[RL] = brake_torque_req;
            writeout_.command.torqueSetpoints[RR] = brake_torque_req;

            //init launch vars
            launch_speed_target = 0;
            time_of_launch = tick.millis;

            //check speed is 0 and brake not pressed
            if ((pedalsData.brakePercent >= launch_ready_brake_threshold)
                || (max_speed >= launch_ready_speed_threshold))
            {
                launch_state = LaunchStates_e::LAUNCH_NOT_READY;
            } else if(pedalsData.accelPercent >= launch_go_accel_threshold){
                launch_state = LaunchStates_e::LAUNCHING;
            }

            //check accel above launch threshold and launch
            break;
        case LaunchStates_e::LAUNCHING:
            { // use brackets to ignore 'cross initialization' of secs_since_launch
            //check accel below launch threshold and brake above
            if((pedalsData.accelPercent <= launch_stop_accel_threshold)
               || (pedalsData.brakePercent >= launch_ready_brake_threshold))
            {
                launch_state = LaunchStates_e::LAUNCH_NOT_READY;
            }

            /*
            Stolen launch algo from HT07. This ramps up the speed target over time.
            launch rate target is m/s^2 and is the target acceleration rate
            secs_since_launch takes the milliseconds since launch started and converts to sec
            This is then converted to RPM for a speed target
            There is an initial speed target that is your iitial instant acceleration on the wheels
            */
            float secs_since_launch = (float)(tick.millis - time_of_launch) / 1000.0;
            launch_speed_target = (int16_t)((float) secs_since_launch * launch_rate_target_ * METERS_PER_SECOND_TO_RPM);
            launch_speed_target += init_speed_target_;
            launch_speed_target = std::min((int)AMK_MAX_RPM, std::max(0, (int)launch_speed_target));

            writeout_.command.speeds_rpm[FL] = launch_speed_target;
            writeout_.command.speeds_rpm[FR] = launch_speed_target;
            writeout_.command.speeds_rpm[RL] = launch_speed_target;
            writeout_.command.speeds_rpm[RR] = launch_speed_target;

            writeout_.command.torqueSetpoints[FL] = AMK_MAX_TORQUE;
            writeout_.command.torqueSetpoints[FR] = AMK_MAX_TORQUE;
            writeout_.command.torqueSetpoints[RL] = AMK_MAX_TORQUE;
            writeout_.command.torqueSetpoints[RR] = AMK_MAX_TORQUE;

            }
            break;
        default:
            break;



    }
}

void TorqueControllerSlipLaunch::tick(
    const SysTick_s &tick,
    const PedalsSystemData_s &pedalsData,
    const float wheel_rpms[])
{

    int16_t brake_torque_req = pedalsData.regenPercent * MAX_REGEN_TORQUE;

    float max_speed = 0;
    for(int i = 0; i < 4; i++){
        max_speed = std::max(max_speed, abs(wheel_rpms[i]));
    }

    writeout_.ready = true;

    switch(launch_state){
        case LaunchStates_e::LAUNCH_NOT_READY:
            // set torques and speed to 0
            writeout_.command.speeds_rpm[FL] = 0.0;
            writeout_.command.speeds_rpm[FR] = 0.0;
            writeout_.command.speeds_rpm[RL] = 0.0;
            writeout_.command.speeds_rpm[RR] = 0.0;

            writeout_.command.torqueSetpoints[FL] = brake_torque_req;
            writeout_.command.torqueSetpoints[FR] = brake_torque_req;
            writeout_.command.torqueSetpoints[RL] = brake_torque_req;
            writeout_.command.torqueSetpoints[RR] = brake_torque_req;

            //init launch vars
            launch_speed_target = 0;
            time_of_launch = tick.millis;
            // check speed is 0 and pedals not pressed
            if((pedalsData.accelPercent < launch_ready_accel_threshold)
               && (pedalsData.brakePercent < launch_ready_brake_threshold)
               && (max_speed < launch_ready_speed_threshold))
            {
                launch_state = LaunchStates_e::LAUNCH_READY;
            }

            break;
        case LaunchStates_e::LAUNCH_READY:
            // set torques and speed to 0
            writeout_.command.speeds_rpm[FL] = 0.0;
            writeout_.command.speeds_rpm[FR] = 0.0;
            writeout_.command.speeds_rpm[RL] = 0.0;
            writeout_.command.speeds_rpm[RR] = 0.0;

            writeout_.command.torqueSetpoints[FL] = brake_torque_req;
            writeout_.command.torqueSetpoints[FR] = brake_torque_req;
            writeout_.command.torqueSetpoints[RL] = brake_torque_req;
            writeout_.command.torqueSetpoints[RR] = brake_torque_req;

            //init launch vars
            launch_speed_target = 0;
            time_of_launch = tick.millis;

            //check speed is 0 and brake not pressed
            if ((pedalsData.brakePercent >= launch_ready_brake_threshold)
                || (max_speed >= launch_ready_speed_threshold))
            {
                launch_state = LaunchStates_e::LAUNCH_NOT_READY;
            } else if(pedalsData.accelPercent >= launch_go_accel_threshold){
                launch_state = LaunchStates_e::LAUNCHING;
            }

            //check accel above launch threshold and launch
            break;
        case LaunchStates_e::LAUNCHING:
            { // use brackets to ignore 'cross initialization' of secs_since_launch
            //check accel below launch threshold and brake above
            if((pedalsData.accelPercent <= launch_stop_accel_threshold)
               || (pedalsData.brakePercent >= launch_ready_brake_threshold))
            {
                launch_state = LaunchStates_e::LAUNCH_NOT_READY;
            }

            uint32_t ms_since_launch = (tick.millis - time_of_launch);
            // accelerate at constant speed for a period of time to get body velocity up
            // may want to make this the ht07 launch algo
            if(ms_since_launch < const_accel_time){

                launch_speed_target = DEFAULT_LAUNCH_SPEED_TARGET;

            } else {

                /*
                New slip-ratio based launch algorithm by Luke Chen. The basic idea
                is to always be pushing the car a certain 'slip_ratio_' faster than
                the car is currently going, theoretically always keeping the car in slip
                */
                launch_speed_target = (1 + slip_ratio_) * body_velocity;
                launch_speed_target *= METERS_PER_SECOND_TO_RPM;

            }

            writeout_.command.speeds_rpm[FL] = launch_speed_target;
            writeout_.command.speeds_rpm[FR] = launch_speed_target;
            writeout_.command.speeds_rpm[RL] = launch_speed_target;
            writeout_.command.speeds_rpm[RR] = launch_speed_target;

            writeout_.command.torqueSetpoints[FL] = AMK_MAX_TORQUE;
            writeout_.command.torqueSetpoints[FR] = AMK_MAX_TORQUE;
            writeout_.command.torqueSetpoints[RL] = AMK_MAX_TORQUE;
            writeout_.command.torqueSetpoints[RR] = AMK_MAX_TORQUE;

            }
            break;
        default:
            break;



    }
}

void TorqueControllerPIDTV::tick(const SysTick_s &tick, const PedalsSystemData_s &pedalsData, float vx_b, float wheel_angle_rad, float yaw_rate)
{

    pid_input_.Vx_B = vx_b;
    pid_input_.WheelDeltarad = wheel_angle_rad;
    pid_input_.YawRaterads = yaw_rate;
    pid_input_.FR_in = 1.0;
    pid_input_.RR_in = 1.0;
    pid_input_.FL_in = 1.0;
    pid_input_.RL_in = 1.0;

    tv_pid_.step();
    const PID_TV::ExtY_PID_TV_T& out = tv_pid_.getExternalOutputs();
    
}
