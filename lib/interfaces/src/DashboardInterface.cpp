#include "DashboardInterface.h"

DashComponentInterface DashDriver::evaluate_dashboard(const Dashboard_status &data) 
{
    DashComponentInterface out;
    out.dial_mode = static_cast<DialMode>(data.get_dial_state());
    return out;
}

