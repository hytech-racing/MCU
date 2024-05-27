#ifndef THERMISTORINTERFACE
#define THERMISTORINTERFACE
#include "stdint.h"
#include <math.h>
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "MessageQueueDefine.h"
#include "AnalogSensorsInterface.h"
#include "hytech.h"
#include "Thermistor.h"


const int NUM_FRONT_THERMISTORS = 2;

class ThermistorInterface 
{
private:
    Thermistors<
     
    float therm_fl;
    float therm_fr;

     CANBufferType *_msg_queue;

     float convert(int raw);

public:
    ThermistorInterface(CANBufferType *msg_output_queue);
    ThermistorInterface(CANBufferType *msg_output_queue, const float beta, const uint16_t adc_saturation, const float zero_kelvin, const float t0_celcius, const float r_nom, const float r0);
    
    void convert(const AnalogConversion_s &raw_therm_fl, const AnalogConversion_s &raw_therm_fr);

    void update_front_thermistor_readings();
    
    template <typename U>
    void enqueue_CAN_front_thermistors(U *structure, uint32_t (*pack_function)(U *, uint8_t *, uint8_t *, uint8_t *));
    
    void tick(const AnalogConversion_s &raw_therm_fl, const AnalogConversion_s &raw_therm_fr);

};






#endif