#ifndef THERMISTORINTERFACE
#define THERMISTORINTERFACE
#include "stdint.h"
#include <math.h>
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "MessageQueueDefine.h"
#include "AnalogSensorsInterface.h"
#include "hytech.h"
#include "MCU_rev15_defs.h"
#include "Thermistor.h"


class ThermistorInterface 
{
private:
    Thermistors<2> front_thermistors;
     
    float therm_fl;
    float therm_fr;

     CANBufferType *_msg_queue;

     float convert(int raw);

public:
    ThermistorInterface(CANBufferType *msg_output_queue);
    void update_front_thermistor_readings();
    
    template <typename U>
    void enqueue_CAN_front_thermistors(U *structure, uint32_t (*pack_function)(U *, uint8_t *, uint8_t *, uint8_t *));
    
    void tick(const AnalogConversion_s &raw_therm_fl, const AnalogConversion_s &raw_therm_fr);

};






#endif