#ifndef INVERTERINTERFACE
#define INVERTERINTERFACE
struct InverterCommand
{
    float torque_setpoint_nm;
    float speed_setpoint_rpm;
};

#endif /* INVERTERINTERFACE */
