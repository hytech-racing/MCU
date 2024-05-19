#ifndef THERMISTORINTERFACE
#define THERMISTORINTERFACE
#include "stdint.h"
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "MessageQueueDefine.h"
#include "hytech.h"


const float DEFAULT_THERM_BETA = 3606.05;
const uint16_t DEFAULT_ADC_SATUR = 4095;
const float DEFAULT_ZERO_KELVIN = 273.15;
const float DEFAULT_T0_CELCIUS = 25;
const float DEFAULT_R_NOM = 10000;
const float DEFAULT_R0 = 8350;

class ThermistorInterface 
{
private:
     float _beta;
     uint16_t _adc_saturation;
     float _zero_kelvin;
     float _t0_celcius;
     float _r_nom;
     float _r0;
     
     int16_t therm_fl;
     int16_t therm_fr;

     CANBufferType *msq_queue_;

     float convert(int raw);

public:
    ThermistorInterface(CANBufferType *msg_output_queue);
    ThermistorInterface(CANBufferType *msg_output_queue, float beta, uint16_t adc_saturation, float zero_kelvin, float to_celcius, float r_nom, float r0);
    
    void convert(const AnalogConversion_s &raw_therm_fl, const AnalogConversion_s &raw_therm_fr);

    void update_front_thermistor_readings();
    
    template <typename U>
    void enqueue_new_CAN(U *structure, uint32_t (*pack_function)(U *, uint8_t *, uint8_t *, uint8_t *));
    
    void tick(const AnalogConversion_s &raw_therm_fl, const AnalogConversion_s &raw_therm_fr);

}






#endif