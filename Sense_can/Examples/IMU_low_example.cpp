#ifndef __IMXRT1062__
  #error "This sketch should be compiled for Teensy 4.x"
#endif

#include <ACAN_T4.h>
#include <Sense_can.h>

float array[] = {1.0,2.3};
int addr = 0x13;
Sense_can can;

void setup () {
  can.Setup_can( 50*1000); //set bit rate of can
}
void loop () {
  can.send2data(array, addr);
}
