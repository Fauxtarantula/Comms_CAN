#include "thruster_can.h"

/**
 * Starts the can bus with RX on A11 and TX on 
*/
thrusterCAN::begin() {
  _can.begin(STD_ID_LEN, BR250K, PORTA_11_12_WIRE_PULLUP);
  _can.filterMask16Init(0, ID_A, MASK_A, ID_B, MASK_B);
}

/**
 * Checks for CAN messages, if a message with length of 7 is received,
 * updates array passed in and returns true
*/
thrusterCAN::receive_speeds(volatile uint8_t data[8]) {
  uint8_t id, fltIdx;
  int len;
  len = _can.receive(id, fltIdx, data);
  return len == 7;
}

/**
 * transmits heartbeat message to SBC
*/
thrusterCAN::transmit_heartbeat() {
  uint8_t txData[1] = {0x00};
  return _can.transmit(HEARTBEAT_ID, txData, 1);
}