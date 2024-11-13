#include "Gyroscope.h"

//init and offset to base 130 (no movement)
void Gyroscope::init() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  mpu.setZGyroOffset(150);
}

//Meant to be used in loop, reads gyro Z (yaw) angular velocity
byte Gyroscope::getZ(){
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  z = map(gz, -32768, 32768, 0, 255); 
  return z - 129; //negative values are clockwise
}
