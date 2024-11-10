#include <StatsSystem.h>

LowLevelStatData_s StatsSystem::get_latest_vehicle_stats(const SharedCarState_s &veh_state)
{
    if (_last_stat_update_timestamp == 0)
    {
        _prev_dt_s = 0.0f;
        _last_stat_update_timestamp = veh_state.systick.millis;
    }
    else
    {
        _prev_dt_s = (veh_state.systick.millis - _last_stat_update_timestamp) / 1000.0f;
    }

    float avg_rpm = 0;
    for (int i = 0; i < NUM_MOTORS; i++)
    {
        avg_rpm += veh_state.drivetrain_data.measuredSpeeds[i];
    }

    avg_rpm = avg_rpm / static_cast<float>(NUM_MOTORS);
    _current_data.session_distance += _prev_dt_s * (avg_rpm * RPM_TO_METERS_PER_SECOND);
    return _current_data;
}