#include "Dashboard.h"

DashComponentInterface DashComponent::evaluate_dashboard(const DashDriverInterface &data) 
{
    DashComponentInterface out;
    out.dial_mode = static_cast<DialMode>(data.dial_position);
}