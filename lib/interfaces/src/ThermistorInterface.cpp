#include "ThermistorInterface.h"




ThermistorInterface::ThermistorInterface(CANBufferType *msg_output_queue, const float beta, const uint16_t adc_saturation, const float zero_kelvin, const float t0_celcius, const float r_nom, const float r0)
{
    _msg_queue = msg_output_queue;
    _beta = beta;
    _adc_saturation = adc_saturation;
    _zero_kelvin = zero_kelvin;
    _t0_celcius = t0_celcius;
    _r_nom = r_nom;
    _r0 = r0;
}
ThermistorInterface::ThermistorInterface(CANBufferType *msg_output_queue)
    : ThermistorInterface(msg_output_queue, DEFAULT_THERM_BETA, DEFAULT_ADC_SATUR, DEFAULT_ZERO_KELVIN, DEFAULT_T0_CELCIUS, DEFAULT_R_NOM, DEFAULT_R0) {
}


float ThermistorInterface::convert(int raw) 
{
    float _t0_kelvin = _t0_celcius + _zero_kelvin;
    float resistance;
    float temp_kelvin;
    float temp_celcius;

    resistance = _r0 * raw / (_adc_saturation - raw);
    temp_kelvin = 1/ (1/_t0_kelvin + log(resistance/_r_nom)/_beta);
    temp_celcius = temp_kelvin - _zero_kelvin;
    return temp_celcius;
}

void ThermistorInterface::update_front_thermistor_readings() 
{
    FRONT_THERMISTORS_t front_thermistors_;
    //scale by 500 for easy packing
    front_thermistors_.thermistor_motor_fl = therm_fl * 500;
    front_thermistors_.thermistor_motor_fr = therm_fr * 500;

    enqueue_CAN_front_thermistors<FRONT_THERMISTORS_t>(&front_thermistors_, &Pack_FRONT_THERMISTORS_hytech);
}

template<typename U>
void ThermistorInterface::enqueue_CAN_front_thermistors(U* structure, uint32_t (* pack_function)(U*, uint8_t*, uint8_t*, uint8_t*)) 
{
    CAN_message_t can_msg;
    can_msg.id = pack_function(structure, can_msg.buf, &can_msg.len, (uint8_t*) &can_msg.flags.extended);
    uint8_t buf[sizeof(CAN_message_t)] = {};
    memmove(buf, &can_msg, sizeof(CAN_message_t));
    _msg_queue->push_back(buf, sizeof(CAN_message_t));
}

void ThermistorInterface::tick(const AnalogConversion_s &raw_therm_fl, const AnalogConversion_s &raw_therm_fr) 
{
    therm_fl = convert(raw_therm_fl.raw);
    therm_fr = convert(raw_therm_fr.raw);
    update_front_thermistor_readings();
}