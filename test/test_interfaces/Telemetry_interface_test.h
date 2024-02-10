#ifndef __TELEMETRY_INTERFACE_TEST__
#define __TELEMETRY_INTERFACE_TEST__

#include <Arduino.h>
#include <unity.h>

#include "TelemetryInterface.h"
#include "MessageQueueDefine.h"
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "AnalogSensorsInterface.h"
#include "SteeringEncoderInterface.h"

CANBufferType CAN_tx_test;

void test_telemetry_update_CAN() {
    
    TelemetryInterface telem_interface(&CAN_tx_test);

    // Pedal readings
    AnalogConversion_s accel1;
    AnalogConversion_s accel2;
    AnalogConversion_s brake1;
    AnalogConversion_s brake2;
    accel1.raw = 1;
    accel2.raw = 2;
    brake1.raw = 3;
    brake2.raw = 4;
    telem_interface.update_pedal_readings_CAN_msg(accel1, accel2, brake1, brake2);
    CAN_message_t msg;
    MCU_pedal_readings pedal_can_msg;
    telem_interface.enqueue_CAN_mcu_pedal_readings();
    uint8_t buf[sizeof(CAN_message_t)];
    CAN_tx_test.pop_front(buf, sizeof(CAN_message_t));
    memmove(&msg, buf, sizeof(msg));
    TEST_ASSERT_EQUAL(ID_MCU_PEDAL_READINGS, msg.id);
    pedal_can_msg.load(msg.buf);
    TEST_ASSERT_EQUAL(accel1.raw, pedal_can_msg.get_accelerator_pedal_1());
    TEST_ASSERT_EQUAL(accel2.raw, pedal_can_msg.get_accelerator_pedal_2());
    TEST_ASSERT_EQUAL(brake1.raw, pedal_can_msg.get_brake_pedal_1());
    TEST_ASSERT_EQUAL(brake2.raw, pedal_can_msg.get_brake_pedal_2());

    // Analog readings
    SteeringEncoderConversion_s steer1;
    AnalogConversion_s steer2;
    AnalogConversion_s current;
    AnalogConversion_s reference;
    AnalogConversion_s glv;
    steer1.angle = 1234.567890;
    steer2.raw = 45;
    current.raw = 67;
    reference.raw = 23;
    glv.raw = 178;
    telem_interface.update_analog_readings_CAN_msg(steer1, steer2, current, reference, glv);
    MCU_analog_readings analog_can_msg;
    telem_interface.enqueue_CAN_mcu_analog_readings();
    CAN_tx_test.pop_front(buf, sizeof(CAN_message_t));
    memmove(&msg, buf, sizeof(msg));
    TEST_ASSERT_EQUAL(ID_MCU_ANALOG_READINGS, msg.id);
    analog_can_msg.load(msg.buf);
    TEST_ASSERT_EQUAL(static_cast<int16_t>(steer1.angle * 10000), analog_can_msg.get_steering_1());
    TEST_ASSERT_EQUAL(steer2.raw, analog_can_msg.get_steering_2());
    TEST_ASSERT_EQUAL(current.raw - reference.raw, analog_can_msg.get_hall_effect_current());
    TEST_ASSERT_EQUAL(glv.raw, analog_can_msg.get_glv_battery_voltage());

    // Front load cells
    AnalogConversion_s lc_fl;
    AnalogConversion_s lc_fr;
    lc_fl.raw = 107;
    lc_fr.raw = 93;
    telem_interface.update_load_cells_CAN_msg(lc_fl, lc_fr);
    MCU_load_cells load_cells_can_msg;
    telem_interface.enqueue_CAN_mcu_load_cells();
    CAN_tx_test.pop_front(buf, sizeof(CAN_message_t));
    memmove(&msg, buf, sizeof(msg));
    TEST_ASSERT_EQUAL(ID_MCU_LOAD_CELLS, msg.id);
    load_cells_can_msg.load(msg.buf);
    TEST_ASSERT_EQUAL(lc_fl.raw, load_cells_can_msg.get_FL_load_cell());
    TEST_ASSERT_EQUAL(lc_fr.raw, load_cells_can_msg.get_FR_load_cell());

    // Front pots
    AnalogConversion_s pots_fl;
    AnalogConversion_s pots_fr;
    pots_fl.raw = 78;
    pots_fr.raw = 90;
    telem_interface.update_potentiometers_CAN_msg(pots_fl, pots_fr);
    MCU_front_potentiometers front_pots_can_msg;
    telem_interface.enqueue_CAN_mcu_front_potentiometers();
    CAN_tx_test.pop_front(buf, sizeof(CAN_message_t));
    memmove(&msg, buf, sizeof(msg));
    TEST_ASSERT_EQUAL(ID_MCU_FRONT_POTS, msg.id);
    front_pots_can_msg.load(msg.buf);
    TEST_ASSERT_EQUAL(pots_fl.raw, front_pots_can_msg.get_pot1());
    TEST_ASSERT_EQUAL(pots_fr.raw, front_pots_can_msg.get_pot3());
}


#endif