#ifndef __PEDALSINTERFACE_H__
#define __PEDALSINTERFACE_H__

#include <tuple>

enum PedalsStatus_s
{
    PEDALS_NOMINAL = 0,
    PEDALS_MARGINAL = 1,
    PEDALS_IMPLAUSIBLE = 2,
};

class PedalsInterface
{
private:
public:
    /// @brief Calculate pedal positions and status (nominal, marginal, implausible). DOES NOT SAMPLE.
    /// @return Accel percent (0.0 - 1.0), brake percent (0.0 - 1.0), PedalsStatus_s
    virtual std::tuple<float, float, PedalsStatus_s> getPedalsAndStatus();
};

#endif /* __PEDALSINTERFACE_H__ */