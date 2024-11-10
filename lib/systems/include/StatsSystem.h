#ifndef __STATSSYSTEM_H__
#define __STATSSYSTEM_H__

#include <SharedDataTypes.h>
#include <Utility.h>

class StatsSystem
{
    public:
        StatsSystem() {
            _prev_dt_s = 0.0f;
            _last_stat_update_timestamp = 0;
            _current_data = {};
        }
        LowLevelStatData_s get_latest_vehicle_stats(const SharedCarState_s& veh_state);
    private: 
        float _prev_dt_s;
        unsigned long _last_stat_update_timestamp;
        LowLevelStatData_s _current_data;

};
#endif // __STATSSYSTEM_H__