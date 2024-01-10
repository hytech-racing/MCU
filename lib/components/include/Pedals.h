
#include <tuple>

struct PedalsDriverInterface {
    int accelPedalPosition1;
    int accelPedalPosition2;
    int brakePedalPosition1;
    int brakePedalPosition2;
};
struct PedalsComponentInterface {
    bool accelImplausible;
    bool brakeImplausible;
    bool isBraking;
    int requestedTorque;
};
class PedalsComponent {
    public:
        PedalsComponent(){
            // Setting of min and maxes for pedals via config file
        };
        PedalsComponentInterface evaluate_pedals(
                const PedalsDriverInterface& pedal_data);

    private:
        std::tuple<int, int> linearize_accel_pedal_values_(int accel1, int accel2);
        bool evaluate_accel_implausibilities_(int accel1, int accel2);
        bool evaluate_brake_implausibilities_(int b1, int b2);

        int min_accel_; 
        int max_accel_;
        int start_accel_1_;
        int start_accel_2_;
        int start_brake_1_;
        int start_brake_2_;
        int end_accel_1_;
        int end_accel_2_;
        int end_brake_1_;
        int end_brake_2_;
        
};