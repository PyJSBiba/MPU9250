# MPU9250
Library for MPU9250

# How to use?
Just drop files into the Arduino project, write `#include "MPU9250.hpp"` and initialize Wire.

For Example

```C++

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
```
