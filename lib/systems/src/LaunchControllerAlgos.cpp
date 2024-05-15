#include "LookupLaunchController.h"
#include "SlipLaunchController.h"
#include "SimpleLaunchController.h"


void TorqueControllerSimpleLaunch::calc_launch_algo(const vectornav &vn_data)
{
    /*
    Stolen launch algo from HT07. This ramps up the speed target over time.
    launch rate target is m/s^2 and is the target acceleration rate
    secs_since_launch takes the milliseconds since launch started and converts to sec
    This is then converted to RPM for a speed target
    There is an initial speed target that is your iitial instant acceleration on the wheels
    */
    float secs_since_launch = (float)(current_millis_ - time_of_launch_) / 1000.0;
    launch_speed_target_ = (int16_t)((float)secs_since_launch * launch_rate_target_ * METERS_PER_SECOND_TO_RPM);
    launch_speed_target_ += init_speed_target_;
    launch_speed_target_ = std::min((int)PhysicalParameters::AMK_MAX_RPM, std::max(0, (int)launch_speed_target_));
}

void TorqueControllerLookupLaunch::calc_launch_algo(const vectornav &vn_data)
{

    launch_speed_target_ = std::max((float)LookupLaunchControllerParams::DEFAULT_LAUNCH_SPEED_TARGET, launch_speed_target_);

    double dx = vn_data.ecef_coords[0] - initial_ecef_x_;
    double dy = vn_data.ecef_coords[1] - initial_ecef_y_;
    double dz = vn_data.ecef_coords[2] - initial_ecef_z_;

    double distance = sqrt((dx * dx) + (dy * dy) + (dz * dz));

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
void TorqueControllerSlipLaunch::calc_launch_algo(const vectornav &vn_data)
{
    // accelerate at constant speed for a period of time to get body velocity up
    // may want to make this the ht07 launch algo

    // makes sure that the car launches at the target launch speed
    launch_speed_target_ = std::max(launch_speed_target_, (float)SlipLaunchControllerParams::DEFAULT_LAUNCH_SPEED_TARGET);

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