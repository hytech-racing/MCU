
#include <tuple>

struct DashDriverInterface {

};
struct DashComponentInterface {

};
class DashComponent {
    public:
        DashComponent(){
            // Setting of min and maxes for pedals via config file
        };
        DashComponentInterface evaluate_dashboard(
                const DashDriverInterface& data);
        bool start_button_pressed();
    private:
        

        
        
};