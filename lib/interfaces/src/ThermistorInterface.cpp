#include "ThermistorInterface.h"


ThermistorInterface::ThermistorInterface(CANBufferType *msg_output_queue) 
{
    this(*msg_output_queue, DEFAULT_THERM_BETA, DEFAULT_ADC_SATUR, DEFAULT_ZERO_KELVIN, DEFAULT_T0_CELCIUS, DEFAULT_R_NOM, DEFAULT_R0);
}

ThermistorInterface::ThermistorInterface(CANBufferType *msg_output_queue, float beta, uint16_t adc_saturation, float zero_kelvin, float to_celcius, float r_nom, float r0)
{
    msg_queue = msg_output_queue;
    _beta = beta;
    _adc_saturation = adc_saturation;
    _zero_kelvin = zero_kelvin;
    _t0_celcius = t0_celcius;
    _r_nom = r_nom;
    _r0 = r0;
}

void ThermistorInterface::convert(const AnalogConversion_s &raw_therm_fl, const AnalogConversion_s &raw_therm_fr)
{
    float _t0_kelvin = _t0_celcius + _zero_kelvin;
    float resistance;
    float temp_kelvin;
    float temp_celcius;
    
    resistance = _r0 * raw_therm_fl.raw / (_adc_saturation - raw_therm_fl.raw);
    temp_kelvin = 1/ (1/t0_kelvin + Math.log(resistance/_r_nom)/beta);
    temp_celcius = temp_kelvin - _zero_kelvin;
    therm_fl = temp_celcius;

    resistance = _r0 * raw_therm_fr.raw / (_adc_saturation - raw_therm_fr.raw);
    temp_kelvin = 1/ (1/t0_kelvin + Math.log(resistance/_r_nom)/beta);
    temp_celcius = temp_kelvin - _zero_kelvin;
    therm_fr = temp_celcius;
}

float ThermistorInterface::convert(int raw) {
    float _t0_kelvin = _t0_celcius + _zero_kelvin;
    float resistance;
    float temp_kelvin;
    float temp_celcius;

    resistance = _r0 * raw / (_adc_saturation - raw);
    temp_kelvin = 1/ (1/t0_kelvin + Math.log(resistance/_r_nom)/beta);
    temp_celcius = temp_kelvin - _zero_kelvin;
    return temp_celcius;
}

void ThermistorInterface::update_front_thermistor_readings() {
    
}