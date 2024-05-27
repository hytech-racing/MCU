#include "ThermistorInterface.h"




ThermistorInterface::ThermistorInterface(CANBufferType *msg_output_queue)
{
    _msg_queue = msg_output_queue;
    
}
ThermistorInterface::ThermistorInterface(CANBufferType *msg_output_queue)
    : ThermistorInterface(msg_output_queue) {
}



void ThermistorInterface::update_front_thermistor_readings() 
{
    FRONT_THERMISTORS_t front_thermistors_;
    //scale by 500 for easy packing
    front_thermistors_.thermistor_motor_fl_ro = HYTECH_thermistor_motor_fl_ro_toS(therm_fl);
    front_thermistors_.thermistor_motor_fr_ro = HYTECH_thermistor_motor_fr_ro_toS(therm_fr);

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

    therm_fl = front_thermistors.get(MCU15_THERM_FL_CHANNEL).convert(raw_therm_fl.raw);
    therm_fr = front_thermistors.get(MCU15_THERM_FR_CHANNEL).convert(raw_therm_fr.raw);
    update_front_thermistor_readings();
}