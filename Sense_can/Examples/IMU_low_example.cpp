#ifndef __IMXRT1062__
  #error "This sketch should be compiled for Teensy 4.x"
#endif

#include <ACAN_T4.h>
#include <Sense_can.h>

float array[] = {1.0,2.3};
void setup () {
  Sense_can startup;
  startup.Setup_can(9600, 250*1000);
}
void loop () {
  Sense_can instance;
  instance.IMU_low(array);
}
