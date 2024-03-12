#include <Arduino.h>
#define ACCEPTABLE_ERROR_COUNT 10
#define ACCEPTABLE_MILLIS_ERROR 50

class LatencyTest {
    public:
        LatencyTest(){}

        bool chilling = true;
        int error_count = 0;
        bool first_time = true;

        int errors[ACCEPTABLE_ERROR_COUNT];
        
        unsigned long top_of_loop = 0;
        unsigned long state_machine = 0;
        unsigned long safety_system = 0;
        unsigned long bottom_of_loop = 0;

        unsigned long last_error = 0;

        void check_results(){
            if (!first_time){
                we_chilling();
                if (!chilling) print_results();
            } else {
                first_time = false;
                top_of_loop = millis();
                bottom_of_loop = millis();
            }
            if(!chilling) {
                last_error = millis();
            }
            top_of_loop = millis();
        }
        void print_results(){
                Serial.printf("CHILLING: %d\n", chilling);
                Serial.printf("ERROR COUNT: %d\n", error_count);
                Serial.printf("Total Loop: %d\n", (bottom_of_loop - top_of_loop));
                Serial.printf("Time since last error %d\n",(millis() - last_error));
                Serial.printf("Safety System Time: %d\n", (safety_system - state_machine));
                top_of_loop = millis();
                Serial.printf("Time on back of loop: %d\n", (top_of_loop - bottom_of_loop));
        }
        void we_chilling(){
            chilling = (bottom_of_loop - top_of_loop) < ACCEPTABLE_MILLIS_ERROR;
            if (!chilling) {
                error_count++;
                // errors[error_count] = (bottom_of_loop - top_of_loop);
            }
            if (error_count >= ACCEPTABLE_ERROR_COUNT){
                print_results();
                // for (int i = 0; i < error_count; i++){
                //     Serial.printf("%d,",errors[error_count]);
                // }
                while (true) {
                    digitalWrite(LED_BUILTIN, HIGH);
                    delay(500);
                    digitalWrite(LED_BUILTIN, LOW);
                    delay(500);
                }
            }
        }
    private:

};