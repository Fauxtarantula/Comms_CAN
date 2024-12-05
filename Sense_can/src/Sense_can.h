#pragma once

#ifndef __IMXRT1062__
  #error "Check whether teensy"
#endif

#include "ACAN_T4.h"

class Sense_can{
  public : void Setup_can(int baudrate, int bitrate);
  public : void IMU_low(float data[2], int addr, uint32_t timebuff);
  public : void IMU_hi_depth(float data[2], int addr, uint32_t timebuff);

  public : void Heartbeat(); //done in setup to check ping with jetson
};