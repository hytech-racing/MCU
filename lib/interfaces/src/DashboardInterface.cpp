#include "DashboardInterface.h"

DashSystemInterface DashboardInterface::evaluate_dashboard(const Dashboard_status &data) 
{
    DashSystemInterface out;
    out.dial_mode = static_cast<DialMode>(data.get_dial_state());
    return out;
}

