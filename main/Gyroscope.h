#pragma once // acts as header gaurd

#include <I2Cdev.h> //For binary address for values
#include <Wire.h> //Wire library for MPU
#include <MPU6050.h> //MPU6050 library for Gyroscope

class Gyroscope {
  
  public:
  void init();

  float getZ();
  float getAngle();

  private:
  int16_t gz;
  MPU6050 mpu;
  float z;
  float gzOff;
  unsigned long lastTime;
  float angleZ;
};
