#include <cstdint>
#include "SysClock.h"
#include <algorithm>  // For std::min

struct BmsVoltages {
    uint16_t low_voltage_ro;
};

struct BmsTemperatures {
    uint16_t high_temperature;
};

struct EmMeasurements {
    float em_current_ro;
};

struct AcuShuntMeasurements {
    float current_shunt_read_ro;
};

float currentfromS(float x);
float currentshuntfromS(float x);
float lowvoltagefromS(float x);

const unsigned short MAX_PACK_CHARGE      = 48600;

class AMSSystem {
public:
    AMSSystem();

    float initialize_charge();
    void tick(const SysTick_s &tick);
    void calculate_SoC_em(const SysTick_s &tick);
    void calculate_SoC_acu(const SysTick_s &tick);
    void calculate_acc_derate_factor();
    float get_acc_derate_factor();
    float get_filtered_max_cell_temp();
    float get_filtered_min_cell_voltage();
    float bms_high_temp;
    float cell_temp_alpha;
    float cell_voltage_alpha;
    float bms_low_voltage;
    
    // Helper function
    static float map_range(float value, float in_min, float in_max, float out_min, float out_max);
    // Variables
    BmsVoltages bms_voltages_;
    BmsTemperatures bms_temperatures_;
    EmMeasurements em_measurements_;
    AcuShuntMeasurements acu_shunt_measurements_;

    unsigned long timestamp_start_;
    SysTick_s last_tick_;
    float charge_;
    float SoC_;
    float acc_derate_factor;
    bool has_initialized_charge_;
    bool use_em_for_soc_;
    float filtered_max_cell_temp;
    float filtered_min_cell_voltage;

    // Constants
    static constexpr float DEFAULT_INIT_TEMP = 40.0;
    static constexpr float DEFAULT_INIT_VOLTAGE = 3.5;
    static constexpr float DEFAULT_TEMP_ALPHA = 0.8;
    static constexpr float DEFAULT_VOLTAGE_ALPHA = 0.8;
    static constexpr unsigned long DEFAULT_INITIALIZATION_WAIT_INTERVAL = 5000;

    // Lookup table for voltage to charge mapping
    const float VOLTAGE_LOOKUP_TABLE[101] = {3.972, 3.945, 3.918, 3.891, 3.885, 3.874, 3.864, 3.858, 3.847, 3.836, 3.82, 3.815, 3.815, 3.798, 3.788,
    3.782, 3.771, 3.755, 3.744, 3.744, 3.733, 3.728, 3.723, 3.712, 3.701, 3.695, 3.69, 3.679, 3.679, 3.668, 3.663, 3.657, 3.647,
    3.647, 3.636, 3.625, 3.625, 3.625, 3.614, 3.609, 3.603, 3.603, 3.592, 3.592, 3.592, 3.581, 3.581, 3.571, 3.571, 3.571, 3.56,
    3.56, 3.56, 3.549, 3.549, 3.549, 3.549, 3.538, 3.538, 3.551, 3.546, 3.535, 3.535, 3.535, 3.53, 3.524, 3.524, 3.524, 3.513,
    3.513, 3.513, 3.503, 3.503, 3.492, 3.492, 3.492, 3.487, 3.481, 3.481, 3.476, 3.471, 3.46, 3.46, 3.449, 3.444, 3.428, 3.428,
    3.417, 3.401, 3.39, 3.379, 3.363, 3.331, 3.299, 3.267, 3.213, 3.149, 3.041, 3, 3, 0};
};
