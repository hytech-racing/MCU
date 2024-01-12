

struct SteeringDriverInterface {
    int steeringChannel1;
    int steeringChannel2;
};

class SteeringComponent {
    public:
        SteeringComponent(){
            // TODO change scaling factors with params
        }
        float get_desired_angle(const SteeringDriverInterface& data);
    private:
        float scaling_;
};
