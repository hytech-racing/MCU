#include <Arduino.h>
#include <unity.h>

#include "hytech.h"
#include "DashboardInterface.h"

Circular_Buffer <uint8_t, (uint32_t)16, sizeof(CAN_message_t)> CAN_buffer;

/* CHAT GPT FUNCTIONS */
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


void test_dashboard_unpacking_can_message(void)
{
  DashboardInterface dash_interface(&CAN_buffer);

  // Chat GPT code that iterates through a truth table
  for (int i = 0; i < (1 << 10); ++i) { // 2^10 possible combinations
      DASHBOARD_STATE_t current_state;
      current_state.start_button = (uint8_t)((i & (1 << 9)) >> 9);
      current_state.mark_button = (uint8_t)((i & (1 << 8)) >> 8);
      current_state.mode_button = (uint8_t)((i & (1 << 7)) >> 7);
      current_state.motor_controller_cycle_button = (uint8_t)((i & (1 << 6)) >> 6);
      current_state.launch_ctrl_button = (uint8_t)((i & (1 << 5)) >> 5);
      current_state.torque_mode_button = (uint8_t)((i & (1 << 4)) >> 4);
      current_state.led_dimmer_button = (uint8_t)((i & (1 << 3)) >> 3);
      current_state.left_shifter_button = (uint8_t)((i & (1 << 2)) >> 2);
      current_state.right_shifter_button = (uint8_t)((i & (1 << 1)) >> 1);
      current_state.shutdown_h_above_threshold = (uint8_t)(i & 1);
      
      CAN_message_t msg;
      msg.id= Pack_DASHBOARD_STATE_hytech(&current_state, msg.buf, &msg.len, (uint8_t*) &msg.flags.extended);

      dash_interface.read(msg);

      TEST_ASSERT_EQUAL(current_state.start_button, dash_interface.startButtonPressed() );
      TEST_ASSERT_EQUAL(current_state.mark_button, dash_interface.specialButtonPressed() );
      TEST_ASSERT_EQUAL(current_state.mode_button , dash_interface.torqueButtonPressed() );
      TEST_ASSERT_EQUAL(current_state.motor_controller_cycle_button, dash_interface.inverterResetButtonPressed() );
      TEST_ASSERT_EQUAL(current_state.launch_ctrl_button , dash_interface.launchControlButtonPressed() );
      TEST_ASSERT_EQUAL(current_state.torque_mode_button , dash_interface.torqueLoadingButtonPressed() );
      TEST_ASSERT_EQUAL(current_state.led_dimmer_button , dash_interface.nightModeButtonPressed() );
      TEST_ASSERT_EQUAL(current_state.left_shifter_button, dash_interface.leftShifterButtonPressed() );
      TEST_ASSERT_EQUAL(current_state.right_shifter_button , dash_interface.rightShifterButtonPressed() );
      TEST_ASSERT_EQUAL(current_state.shutdown_h_above_threshold , dash_interface.shutdownHAboveThreshold() );

  }

    

}

void test_dashboard_circular_buffer(void)
{

    Circular_Buffer <uint8_t, (uint32_t)16, sizeof(CAN_message_t)> CAN_buffer_2;
    DashboardInterface dash_interface(&CAN_buffer_2);

    uint8_t LED[12] = {};

    // for (uint64_t i = 0; i < (1 << 48); ++i) { // 2^48 possible combinations
    //     for (int j = 0; j < 12; ++j) {
    //         int color_index = (i >> (j * 2)) & 0b11; // Extract 2 bits for each LED
    //         switch (color_index) {
    //             case 0:
    //                 LED[j] = static_cast<uint8_t>(LEDColors_e::OFF);
    //                 break;
    //             case 1:
    //                 LED[j] = static_cast<uint8_t>(LEDColors_e::ON);
    //                 break;
    //             case 2:
    //                 LED[j] = static_cast<uint8_t>(LEDColors_e::YELLOW);
    //                 break;
    //             case 3:
    //                 LED[j] = static_cast<uint8_t>(LEDColors_e::RED);
    //                 break;
    //         }
    //     }
        
    //     // Use LED array as needed
    //     // For example, you can print the LED colors:
    //     for (int k = 0; k < 12; ++k) {
    //         Serial.print(LED[k]);
    //         Serial.print(" ");
    //     }
    //     Serial.println();
    // }

    LED[0] = static_cast<uint8_t>(LEDColors_e::RED);
    LED[1] = static_cast<uint8_t>(LEDColors_e::YELLOW);


    dash_interface.setLED(DashLED_e::BOTS_LED, LEDColors_e::RED);
    dash_interface.setLED(DashLED_e::LAUNCH_CONTROL_LED, LEDColors_e::YELLOW);

    // need to make _data in dash interface public:
    // TODO: investigate using friend class
    // TEST_ASSERT_EQUAL_UINT8_ARRAY(LED, dash_interface._data.LED, sizeof(LED));
    
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

    TEST_ASSERT_EQUAL(LEDColors_e::RED, mcu_state.bots_led);
    TEST_ASSERT_EQUAL(LEDColors_e::YELLOW, mcu_state.launch_control_led);

}