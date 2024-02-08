#include <Arduino.h>
#include <unity.h>

#include "hytech.h"
#include "DashboardInterface.h"

Circular_Buffer <uint8_t, (uint32_t)16, sizeof(CAN_message_t)> CAN_buffer;

void setUp(void)
{

}

void tearDown(void)
{

}

void printMemoryHex(void* ptr, size_t length) {
  uint8_t* bytePtr = (uint8_t*)ptr;
  for (size_t i = 0; i < length; ++i) {
    if (bytePtr[i] < 0x10) {
      Serial.print("0"); // Add leading zero for values less than 0x10
    }
    Serial.print(bytePtr[i], HEX);
    Serial.print(' ');
  }
  Serial.println();
}

void test_unpacking_can_message(void)
{
    DashboardInterface dash_interface(&CAN_buffer);

    DASHBOARD_STATE_t dash_state{};
    dash_state.start_button = true;
    dash_state.mark_button = true;
    dash_state.mode_button = false;
    dash_state.motor_controller_cycle_button = true;
    dash_state.launch_ctrl_button = false;
    dash_state.torque_mode_button = false;
    dash_state.led_dimmer_button = false;
    dash_state.left_shifter_button = true;
    dash_state.right_shifter_button = false;
    dash_state.shutdown_h_above_threshold = false;

    CAN_message_t msg;
    msg.id= Pack_DASHBOARD_STATE_hytech(&dash_state, msg.buf, &msg.len, (uint8_t*) &msg.flags.extended);

    dash_interface.read(msg);

    TEST_ASSERT_EQUAL(dash_state.start_button, dash_interface.startButtonPressed() );
    TEST_ASSERT_EQUAL(dash_state.mark_button, dash_interface.specialButtonPressed() );
    TEST_ASSERT_EQUAL(dash_state.mode_button , dash_interface.torqueButtonPressed() );
    TEST_ASSERT_EQUAL(dash_state.motor_controller_cycle_button, dash_interface.inverterResetButtonPressed() );
    TEST_ASSERT_EQUAL(dash_state.launch_ctrl_button , dash_interface.launchControlButtonPressed() );
    TEST_ASSERT_EQUAL(dash_state.torque_mode_button , dash_interface.torqueLoadingButtonPressed() );
    TEST_ASSERT_EQUAL(dash_state.led_dimmer_button , dash_interface.nightModeButtonPressed() );
    TEST_ASSERT_EQUAL(dash_state.left_shifter_button, dash_interface.leftShifterButtonPressed() );
    TEST_ASSERT_EQUAL(dash_state.right_shifter_button , dash_interface.rightShifterButtonPressed() );
    TEST_ASSERT_EQUAL(dash_state.shutdown_h_above_threshold , dash_interface.shutdownHAboveThreshold() );

    

}

void test_passing_message_through_circular_buffer(void)
{

    Circular_Buffer <uint8_t, (uint32_t)16, sizeof(CAN_message_t)> CAN_buffer_2;
    DashboardInterface dash_interface(&CAN_buffer_2);

    uint8_t LED[12] = {};
    LED[0] = static_cast<uint8_t>(LEDColors_e::RED);
    LED[1] = static_cast<uint8_t>(LEDColors_e::YELLOW);


    dash_interface.setLED(DashLED_e::BOTS_LED, LEDColors_e::RED);
    dash_interface.setLED(DashLED_e::LAUNCH_CONTROL_LED, LEDColors_e::YELLOW);

    //need to make _data in dash interface public:
    // TODO: investigate using friend class
    TEST_ASSERT_EQUAL_UINT8_ARRAY(LED, dash_interface._data.LED, sizeof(LED));
    
    CAN_message_t packed_message = dash_interface.write();

    uint8_t buffer[sizeof(CAN_message_t)];
    CAN_buffer_2.pop_front(buffer, sizeof(CAN_message_t));

    delay(1000);

    Serial.println("Printing packed message:");
    printMemoryHex(&packed_message, sizeof(CAN_message_t));
    Serial.println("Printing popped message");
    printMemoryHex(&buffer, sizeof(CAN_message_t));

    CAN_message_t msg;
    memmove(&msg, buffer, sizeof(CAN_message_t));

    Serial.println("Printing moved message:");
    printMemoryHex(&msg, sizeof(CAN_message_t));

    TEST_ASSERT_EQUAL_MEMORY(&packed_message, &msg, sizeof(CAN_message_t));

    DASHBOARD_MCU_STATE_t mcu_state;

    Unpack_DASHBOARD_MCU_STATE_hytech(&mcu_state, msg.buf, NULL);

    // TEST_ASSERT_EQUAL(LEDColors_e::RED, mcu_state.bots_led);
    // TEST_ASSERT_EQUAL(LEDColors_e::YELLOW, mcu_state.launch_control_led);

}

int runUnityTests(void) 
{
    UNITY_BEGIN();

    RUN_TEST(test_unpacking_can_message);
    RUN_TEST(test_passing_message_through_circular_buffer);

    return UNITY_END();
}

void setup() 
{
    delay(2000);

    runUnityTests();
}

void loop() {}