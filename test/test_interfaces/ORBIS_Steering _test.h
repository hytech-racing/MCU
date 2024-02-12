#include <Arduino.h>
#include <unity.h>

#include "ORBIS_BR10.h"

void test_steering_sample_and_convert()
{
    OrbisBR10 steering_encoder(&Serial5);

    steering_encoder.sample();

    Serial.println("OrbisBR10 test:");
    Serial.print("Raw: ");
    Serial.println(steering_encoder.convert().raw);
    Serial.print("Angle: ");
    Serial.println(steering_encoder.convert().angle);
    Serial.print("Status: ");
    Serial.println((int)(steering_encoder.convert().status));
}