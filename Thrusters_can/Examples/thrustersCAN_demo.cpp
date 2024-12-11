#include <Arduino.h>
#include "thruster_can.h"

thrusterCAN can;
HardwareSerial serial(PA10, PA9, NC, NC);

uint32_t txDly = 5000; // mSec

void setup() {
  serial.begin(9600);
  can.begin();
  serial.println("CAN initialized");
}

uint32_t last = 0;
void loop() {
  if (millis() / txDly != last)             // tx every txDly
  {
    last = millis() / txDly;
    can.transmit_heartbeat;
    serial.println("sending heartbeat\n");
  }

  uint8_t rxData[8];
  if(can.receive_speeds(rxData)) 
  {
    serial.println("");
    for(int i = 0; i < 7; i += 1) {
      serial.printf("thruster %d speed: %u\n", i, rxData[i]);
    }
    serial.println("");
  }
}