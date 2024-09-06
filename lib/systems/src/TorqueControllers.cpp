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
            // writeout_.command.speeds_rpm[FR] = accelRequest * AMK_MAX_RPM;pid_input_
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
            float netTorqueRequest = torqueRequest * 4;

            writeout_.command.speeds_rpm[FL] = 0.0;
            writeout_.command.speeds_rpm[FR] = 0.0;
            writeout_.command.speeds_rpm[RL] = 0.0;
            writeout_.command.speeds_rpm[RR] = 0.0;



            writeout_.command.torqueSetpoints[FL] = (netTorqueRequest * frontRegenTorqueScale_) / 2;
            writeout_.command.torqueSetpoints[FR] = (netTorqueRequest * frontRegenTorqueScale_) / 2;
            writeout_.command.torqueSetpoints[RL] = (netTorqueRequest * rearRegenTorqueScale_) / 2;
            writeout_.command.torqueSetpoints[RR] = (netTorqueRequest * rearRegenTorqueScale_) / 2;
        }
    }
}

// TorqueControllerLoadCellVectoring

void TorqueControllerLoadCellVectoring::tick(
    const SysTick_s &tick,
    const PedalsSystemData_s &pedalsData,
    float torqueLimit,
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
                
                torquePool = MAX_REGEN_TORQUE * accelRequest * -4.0;

                writeout_.command.speeds_rpm[FL] = 0.0;
                writeout_.command.speeds_rpm[FR] = 0.0;
                writeout_.command.speeds_rpm[RL] = 0.0;
                writeout_.command.speeds_rpm[RR] = 0.0;

                float normalForcePercentFL = loadCellForcesFiltered_[0] / sumNormalForce;
                float normalForcePercentFR = loadCellForcesFiltered_[1] / sumNormalForce;
                float normalForcePercentRL = loadCellForcesFiltered_[2] / sumNormalForce;
                float normalForcePercentRR = loadCellForcesFiltered_[3] / sumNormalForce;

                if (normalForcePercentFL + normalForcePercentFR < .5 || normalForcePercentRL + normalForcePercentRR > .5) {
                    normalForcePercentFL = .25;
                    normalForcePercentFR = .25;
                    normalForcePercentRL = .25;
                    normalForcePercentRR = .25;
                }

                writeout_.command.torqueSetpoints[FL] = torquePool * frontRegenTorqueScale_ * normalForcePercentFL;
                writeout_.command.torqueSetpoints[FR] = torquePool * frontRegenTorqueScale_ * normalForcePercentFR;
                writeout_.command.torqueSetpoints[RL] = torquePool * rearRegenTorqueScale_ * normalForcePercentRL;
                writeout_.command.torqueSetpoints[RR] = torquePool * rearRegenTorqueScale_ * normalForcePercentRR;

                // No load cell vectoring on regen
                // writeout_.command.torqueSetpoints[FL] = torqueRequest * frontRegenTorqueScale_;
                // writeout_.command.torqueSetpoints[FR] = torqueRequest * frontRegenTorqueScale_;
                // writeout_.command.torqueSetpoints[RL] = torqueRequest * rearRegenTorqueScale_;
                // writeout_.command.torqueSetpoints[RR] = torqueRequest * rearRegenTorqueScale_;
            }
        }
        else
        {
            writeout_.command = TC_COMMAND_NO_TORQUE;
        }
    }
}

void BaseLaunchController::tick(
    const SysTick_s &tick,
    const PedalsSystemData_s &pedalsData,
    const float wheel_rpms[],
    const vector_nav* vn_data)
{

    if (tick.triggers.trigger100){

        current_millis_ = tick.millis;

        int16_t brake_torque_req = pedalsData.regenPercent * MAX_REGEN_TORQUE;

        float max_speed = 0;
        for(int i = 0; i < 4; i++){
            max_speed = std::max(max_speed, abs(wheel_rpms[i]));
        }

        writeout_.ready = true;

        switch(launch_state_){
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
                launch_speed_target_ = 0;
                time_of_launch_ = tick.millis;
                // check speed is 0 and pedals not pressed
                if((pedalsData.accelPercent < launch_ready_accel_threshold)
                && (pedalsData.brakePercent < launch_ready_brake_threshold)
                && (max_speed < launch_ready_speed_threshold))
                {
                    launch_state_ = LaunchStates_e::LAUNCH_READY;
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
                launch_speed_target_ = 0;
                time_of_launch_ = current_millis_;

                //check speed is 0 and brake not pressed
                if ((pedalsData.brakePercent >= launch_ready_brake_threshold)
                    || (max_speed >= launch_ready_speed_threshold))
                {
                    launch_state_ = LaunchStates_e::LAUNCH_NOT_READY;
                } else if(pedalsData.accelPercent >= launch_go_accel_threshold){

                    initial_ecef_x_ = vn_data->ecef_coords[0];
                    initial_ecef_y_ = vn_data->ecef_coords[1];
                    initial_ecef_z_ = vn_data->ecef_coords[2];

                    launch_state_ = LaunchStates_e::LAUNCHING;
                }

                //check accel above launch threshold and launch
                break;
            case LaunchStates_e::LAUNCHING:
                { // use brackets to ignore 'cross initialization' of secs_since_launch
                //check accel below launch threshold and brake above
                if((pedalsData.accelPercent <= launch_stop_accel_threshold)
                || (pedalsData.brakePercent >= launch_ready_brake_threshold))
                {
                    launch_state_ = LaunchStates_e::LAUNCH_NOT_READY;
                }

                calc_launch_algo(vn_data);

                writeout_.command.speeds_rpm[FL] = launch_speed_target_;
                writeout_.command.speeds_rpm[FR] = launch_speed_target_;
                writeout_.command.speeds_rpm[RL] = launch_speed_target_;
                writeout_.command.speeds_rpm[RR] = launch_speed_target_;

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
}

void TorqueControllerSimpleLaunch::calc_launch_algo(const vector_nav* vn_data) {
            /*
            Stolen launch algo from HT07. This ramps up the speed target over time.
            launch rate target is m/s^2 and is the target acceleration rate
            secs_since_launch takes the milliseconds since launch started and converts to sec
            This is then converted to RPM for a speed target
            There is an initial speed target that is your iitial instant acceleration on the wheels
            */
            float secs_since_launch = (float)(current_millis_ - time_of_launch_) / 1000.0;
            launch_speed_target_ = (int16_t)((float) secs_since_launch * launch_rate_target_ * METERS_PER_SECOND_TO_RPM);
            launch_speed_target_ += init_speed_target_;
            launch_speed_target_ = std::min((int)AMK_MAX_RPM, std::max(0, (int)launch_speed_target_));
}

// void TorqueControllerSlipLaunch::calc_launch_algo(const vector_nav* vn_data) {
//     // accelerate at constant speed for a period of time to get body velocity up
//     // may want to make this the ht07 launch algo
    
//     // makes sure that the car launches at the target launch speed
//     launch_speed_target_ = std::max(launch_speed_target_, (float)DEFAULT_LAUNCH_SPEED_TARGET);

//     /*
//     New slip-ratio based launch algorithm by Luke Chen. The basic idea
//     is to always be pushing the car a certain 'slip_ratio_' faster than
//     the car is currently going, theoretically always keeping the car in slip
//     */
//     // m/s
//     float new_speed_target = (1 + slip_ratio_) * (vn_data->velocity_x);
//     // rpm
//     new_speed_target *= METERS_PER_SECOND_TO_RPM;
//     // makes sure the car target speed never goes lower than prev. target
//     // allows for the vn to 'spool' up and us to get reliable vx data
//     launch_speed_target_ = std::max(launch_speed_target_, new_speed_target);
// }

// void TorqueControllerLookupLaunch::calc_launch_algo(const vector_nav* vn_data) {

//     launch_speed_target_ = std::max((float)DEFAULT_LAUNCH_SPEED_TARGET, launch_speed_target_);

//     double dx = vn_data->ecef_coords[0] - initial_ecef_x_;
//     double dy = vn_data->ecef_coords[1] - initial_ecef_y_;
//     double dz = vn_data->ecef_coords[2] - initial_ecef_z_;

//     double distance = sqrt((dx*dx) + (dy*dy) + (dz*dz));

//     /*
//     Distance-lookup launch algorithm. Takes in the vel_dist_lookup
//     generated from Luke's matlab/symlink to set speed targets based
//     on distance travelled from the start point.
//     This can also and may be better to replace with an integration
//     of body velocity.
//     */

//     uint32_t idx = (uint32_t)(distance * 10); // multiply by 10 to be used as index for meters in steps of 1/10
//     idx = std::min(idx, (uint32_t)(sizeof(vel_dist_lookup) / sizeof(float)));
//     float mps_target = vel_dist_lookup[idx];

//     float new_speed_target = mps_target * METERS_PER_SECOND_TO_RPM;
//     launch_speed_target_ = std::max(launch_speed_target_, new_speed_target);

// }

void TorqueControllerCASEWrapper::tick(const TCCaseWrapperTick_s &intake)
{

    for (int i = 0; i < NUM_MOTORS; i++)
    {
        writeout_.command.speeds_rpm[i] = intake.command.speeds_rpm[i];
        writeout_.command.torqueSetpoints[i] = intake.command.torqueSetpoints[i];
    }
    
    writeout_.ready = intake.steeringData.status != SteeringSystemStatus_e::STEERING_SYSTEM_ERROR;
    
}