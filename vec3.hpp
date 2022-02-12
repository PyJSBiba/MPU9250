#include <Arduino.h>

class vec3{
public:
    float x,y,z;
    vec3 operator+(const vec3& vec){
        return {x+vec.x, y+vec.y, z+vec.z};
    }
    vec3 operator-(const vec3& vec){
        return {x-vec.x, y-vec.y, z-vec.z};
    }
    vec3 operator-(){
        return {-x,-y,-z};
    }
    vec3 operator*(const float& var){
        return {x*var,y*var,z*var};
    }
    vec3 operator/(const float& var){
        return {x/var,y/var,z/var};
    }
    vec3 operator*(const vec3& vec){
        return {x*vec.x, y*vec.y, z*vec.z};
    }
    vec3& operator+=(const vec3& vec){
        x+=vec.x;
        y+=vec.y;
        z+=vec.z;
        return *this;
    }
    vec3& operator-=(const vec3& vec){
        x-=vec.x;
        y-=vec.y;
        z-=vec.z;
        return *this;
    }
    vec3& operator*=(const float& var){
        x*=var;
        y*=var;
        z*=var;
        return *this;
    }
    vec3& operator/=(const float& var){
        x/=var;
        y/=var;
        z/=var;
        return *this;
    }
    double length(){
        return sqrt(x*x+y*y+z*z);
    }
    vec3 Normalized(){
        return *this / this->length();
    }

    operator String(){
        String str = "x: ";
        str += String(x,3);
        str += String(" y: ");
        str += String(y,3);
        str += String(" z: ");
        str += String(z,3);
        return str;
    }

    vec3(){}
    vec3(const float& x) : x(x){}
    vec3(const float& x, const float& y) : x(x), y(y){}
    vec3(const float& x, const float& y, const float& z) : x(x), y(y), z(z){}
};

typedef union VecPacket{
    vec3 Vec;
    char Packet[sizeof(vec3)];
};
