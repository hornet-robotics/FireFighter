#include "Gyroscope.h"
#include "HardwareSerial.h"

void Gyroscope::init(int p) {

  Serial.begin(9600);
  Wire.begin();
//init MPU6050
  Serial.println("Initializing MPU6050");
  if(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){
    Serial.println("Could not find a valid MPU6050 sensor");
    while(1);
  }

//calibrate Gyroscope
mpu.calibrateGyro();
mpu.setThreshold(3);
}

//*getters and setters*//
void Gyroscope::getX(){
  return x;
}
void Gyroscope::getY(){
  return y;
}
void Gyroscope::getZ(){
  return z;
}
