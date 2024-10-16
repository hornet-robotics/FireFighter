#pragma once // acts as header gaurd

#include <Arduino.h> // include arduino library
#include <Wire.h> //Wire library for MPU
#include <MPU6050> //MPU6050 library for Gyroscope

class Gyroscope {
  
  public:

  void getX();
  void getY();
  void getZ();

  private:
    MPU6050 mpu;
    Vector rawGyro = mpu.readRawGyro();
    float x = rawGyro.XAxis();
    float y = rawGyro.YAxis();
    float z = rawGyro.ZAxis();
};
