#include <Wire.h>
#include <TimerOne.h>
#include "vec3.hpp"

enum GYRO_FULL_SCALE : uint8_t{
    DPS_250 = 0x00,
    DPS_500 = 0x08,
    DPS_1000 = 0x10,
    DPS_2000 = 0x18
};

enum ACC_FULL : uint8_t{
    SCALE_2_G = 0x00,
    SCALE_4_G = 0x08,
    SCALE_8_G = 0x10,
    SCALE_16_G = 0x18
};

void I2Cread(const uint8_t& Address, const uint8_t& Register, const uint8_t& Nbytes, uint8_t* Data){
    Wire.beginTransmission(Address);
    Wire.write(Register);
    Wire.endTransmission();

    Wire.requestFrom(Address,Nbytes);
    uint8_t index = 0;
    while (Wire.available())
        Data[index++]=Wire.read();
}

void I2CwriteByte(const uint8_t& Address, const uint8_t& Register, const uint8_t& Data){
    Wire.beginTransmission(Address);
    Wire.write(Register);
    Wire.write(Data);
    Wire.endTransmission();
}

vec3 MPU9250valuesToAngles(vec3 var){
    return var*(90.f/8192.f);
}

double Radians(const double& var){
    return var*(PI/180);
}
double Angle(const double& var){
    return var*(180/PI);
}

vec3 Radians(const vec3& vec){
    return {Radians(vec.x),Radians(vec.y),Radians(vec.z)};
}
vec3 Angle(const vec3& vec){
    return {Angle(vec.x),Angle(vec.y),Angle(vec.z)};
}



class MPU9250{
    static constexpr const size_t&& addr = 0x68;
    static constexpr const size_t&& mag_addr = 0x0C;

    uint8_t Buf[14];
    uint8_t Mag[7];
public:
    void begin(){
        I2CwriteByte(addr,29,0x06);
        I2CwriteByte(addr,26,0x06);
        I2CwriteByte(addr,27,GYRO_FULL_SCALE::DPS_1000);
        I2CwriteByte(addr,28,ACC_FULL::SCALE_4_G);
        I2CwriteByte(addr,0x37,0x02);
        I2CwriteByte(mag_addr,0x0A,0x02);
    }
    vec3 GetAccelerometerValues(){
        I2Cread(addr,0x3B,14,Buf);
        return vec3((float)(-(Buf[0]<<8 | Buf[1])),(float)(-(Buf[2]<<8 | Buf[3])),(float)((Buf[4]<<8|Buf[5])));
    }
    

    vec3 GetDeltaAccelerometer(){
        static vec3 crntAccelerometer{}, accelerometer{};
        crntAccelerometer = GetAccelerometerValues();
        vec3 delta = crntAccelerometer - accelerometer;
        accelerometer = crntAccelerometer;
        return delta;
    }
    vec3 GetGyroscopeValues(){
        I2Cread(addr,0x3B,14,Buf);
        return vec3((float)(-(Buf[8]<<8 | Buf[9])),(float)(-(Buf[10]<<8 | Buf[11])),(float)((Buf[12]<<8 | Buf[13])));
    }
    vec3 GetDeltaGyroscope(){
        static vec3 crnt{},gyro{};
        crnt = GetGyroscopeValues();
        vec3 delta = crnt - gyro;
        gyro = crnt;
        return delta;
    }
    vec3 GetMagnetometer(){
        I2Cread(mag_addr,0x03,7,Mag);
        return vec3((float)(-(Mag[3]<<8 | Mag[2])),(float)(-(Mag[1]<<8 | Mag[0])),(float)(-(Mag[5]<<8 | Mag[4])));
    }
    vec3 GetDeltaMagnetometer(){
        static vec3 crnt{}, mag{};
        crnt = GetMagnetometer();
        vec3 delta = crnt - mag;
        mag = crnt;
        return delta;
    }
};
