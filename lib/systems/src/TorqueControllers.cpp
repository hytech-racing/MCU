#include "TorqueControllers.h"
#include "Utility.h"
#include <algorithm>
#include "PhysicalParameters.h"

// TorqueControllerSimple

void TorqueControllerSimple::tick(const TorqueControllerInput_s &in)
{

    // Calculate torque commands at 100hz
    if (in.tick.triggers.trigger100)
    {
        float torqueRequest = get_torque_request(in.pedals, in.torqueLimit);

        if (torqueRequest >= 0.0)
        {
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
}

// TorqueControllerLoadCellVectoring

void TorqueControllerLoadCellVectoring::tick(const TorqueControllerInput_s &in)
{
    // Calculate torque commands at 100hz
    if (in.tick.triggers.trigger100)
    {

        ready = in.lc.FIRSaturated;

        if (ready)
        {
            // Calculate total normal force
            float sumNormalForce = 0.0f;
            sumNormalForce += in.lc.loadCellForcesFiltered.FL;
            sumNormalForce += in.lc.loadCellForcesFiltered.FR;
            sumNormalForce += in.lc.loadCellForcesFiltered.RL;
            sumNormalForce += in.lc.loadCellForcesFiltered.RR;

            float torqueRequest = get_torque_request(in.pedals, in.torqueLimit);

            if (torqueRequest >= 0.0)
            {
                // Positive torque request
                // NOTE: using "torquePool" here instead of torqueRequest for legibility
                float torquePool = torqueRequest * 4;

                writeout_.command.speeds_rpm[FL] = AMK_MAX_RPM;
                writeout_.command.speeds_rpm[FR] = AMK_MAX_RPM;
                writeout_.command.speeds_rpm[RL] = AMK_MAX_RPM;
                writeout_.command.speeds_rpm[RR] = AMK_MAX_RPM;

                writeout_.command.torqueSetpoints[FL] = torquePool * frontTorqueScale_ * in.lc.loadCellForcesFiltered.FL / sumNormalForce;
                writeout_.command.torqueSetpoints[FR] = torquePool * frontTorqueScale_ * in.lc.loadCellForcesFiltered.FR / sumNormalForce;
                writeout_.command.torqueSetpoints[RL] = torquePool * rearTorqueScale_ * in.lc.loadCellForcesFiltered.RL / sumNormalForce;
                writeout_.command.torqueSetpoints[RR] = torquePool * rearTorqueScale_ * in.lc.loadCellForcesFiltered.RR / sumNormalForce;
            }
            else
            {
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

void BaseLaunchController::tick(const TorqueControllerInput_s &in)
{

    if (in.tick.triggers.trigger100){

        current_millis_ = in.tick.millis;

        // only get negative torque request, never allow positive torque
        // also don't want to apply regen torque if pressing on accel
        float brake_torque_req = std::min(get_torque_request(in.pedals, in.torqueLimit), 0.0f);

        float max_speed = 0;
        for(int i = 0; i < 4; i++){
            max_speed = std::max(max_speed, abs(in.drivetrain.measuredSpeeds[i]));
        }

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
                time_of_launch_ = in.tick.millis;
                // check speed is 0 and pedals not pressed
                if((in.pedals.accelPercent < launch_ready_accel_threshold)
                && (in.pedals.brakePercent < launch_ready_brake_threshold)
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
                if ((in.pedals.brakePercent >= launch_ready_brake_threshold)
                    || (max_speed >= launch_ready_speed_threshold))
                {
                    launch_state_ = LaunchStates_e::LAUNCH_NOT_READY;
                } else if(in.pedals.accelPercent >= launch_go_accel_threshold){

                    initial_ecef_x_ = in.vn.ecef_coords[0];
                    initial_ecef_y_ = in.vn.ecef_coords[1];
                    initial_ecef_z_ = in.vn.ecef_coords[2];

                    launch_state_ = LaunchStates_e::LAUNCHING;
                }

                //check accel above launch threshold and launch
                break;
            case LaunchStates_e::LAUNCHING:
                { // use brackets to ignore 'cross initialization' of secs_since_launch
                //check accel below launch threshold and brake above
                if((in.pedals.accelPercent <= launch_stop_accel_threshold)
                || (in.pedals.brakePercent >= launch_ready_brake_threshold))
                {
                    launch_state_ = LaunchStates_e::LAUNCH_NOT_READY;
                }

                calc_launch_algo(in.vn);

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

void TorqueControllerSimpleLaunch::calc_launch_algo(const vector_nav &vn_data) {
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

void TorqueControllerSlipLaunch::calc_launch_algo(const vector_nav &vn_data) {
    // accelerate at constant speed for a period of time to get body velocity up
    // may want to make this the ht07 launch algo
    
    // makes sure that the car launches at the target launch speed
    launch_speed_target_ = std::max(launch_speed_target_, (float)DEFAULT_LAUNCH_SPEED_TARGET);

    /*
    New slip-ratio based launch algorithm by Luke Chen. The basic idea
    is to always be pushing the car a certain 'slip_ratio_' faster than
    the car is currently going, theoretically always keeping the car in slip
    */
    // m/s
    float new_speed_target = (1 + slip_ratio_) * (vn_data.velocity_x);
    // rpm
    new_speed_target *= METERS_PER_SECOND_TO_RPM;
    // makes sure the car target speed never goes lower than prev. target
    // allows for the vn to 'spool' up and us to get reliable vx data
    launch_speed_target_ = std::max(launch_speed_target_, new_speed_target);
}

void TorqueControllerLookupLaunch::calc_launch_algo(const vector_nav &vn_data) {

    launch_speed_target_ = std::max((float)DEFAULT_LAUNCH_SPEED_TARGET, launch_speed_target_);

    double dx = vn_data.ecef_coords[0] - initial_ecef_x_;
    double dy = vn_data.ecef_coords[1] - initial_ecef_y_;
    double dz = vn_data.ecef_coords[2] - initial_ecef_z_;

    double distance = sqrt((dx*dx) + (dy*dy) + (dz*dz));

    /*
    Distance-lookup launch algorithm. Takes in the vel_dist_lookup
    generated from Luke's matlab/symlink to set speed targets based
    on distance travelled from the start point.
    This can also and may be better to replace with an integration
    of body velocity.
    */

    uint32_t idx = (uint32_t)(distance * 10); // multiply by 10 to be used as index for meters in steps of 1/10
    idx = std::min(idx, (uint32_t)(sizeof(vel_dist_lookup) / sizeof(float)));
    float mps_target = vel_dist_lookup[idx];

    float new_speed_target = mps_target * METERS_PER_SECOND_TO_RPM;
    launch_speed_target_ = std::max(launch_speed_target_, new_speed_target);

}

// void TorqueControllerCASEWrapper::tick(const TCCaseWrapperTick_s &intake)
// {

//     for (int i = 0; i < NUM_MOTORS; i++)
//     {
//         writeout_.command.speeds_rpm[i] = intake.command.speeds_rpm[i];
//         writeout_.command.torqueSetpoints[i] = intake.command.torqueSetpoints[i];
//     }
    
//     writeout_.ready = intake.steeringData.status != SteeringSystemStatus_e::STEERING_SYSTEM_ERROR;
    
// }