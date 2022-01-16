#include <Arduino.h>
#include "MPU9250.hpp"

MPU9250 mpu;

void setup(){
    Wire.begin();
    Serial.begin(115200);
    mpu.begin();
}
void loop(){
    PrintVec3(MPU9250valuesToAngles(mpu.GetAccelerometerValues()));
    Serial.println("");
}