#ifndef DASHBOARDINTERFACE
#define DASHBOARDINTERFACE
class DashboardInterface
{
private:
public:
    bool start_button_status_;
    bool start_button_pressed() { return  start_button_status_; };
};

#endif /* DASHBOARDINTERFACE */
