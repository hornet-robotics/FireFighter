#pragma once // acts as header gaurd

#include <I2Cdev.h>
#include <Wire.h> //Wire library for MPU
#include <MPU6050.h> //MPU6050 library for Gyroscope

class Gyroscope {
  
  public:
  void init();

  byte getZ();

  private:
  int16_t ax, ay, az;
  int16_t gx, gy, gz; //ignore all but gz
  MPU6050 mpu;
  byte z;
};
