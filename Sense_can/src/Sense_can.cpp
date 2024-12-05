#include "Sense_can.h"
#include "ACAN_T4.h"
#include "ACAN_T4_Settings.h"

void Sense_can :: Setup_can(int baudrate, int bitrate){
pinMode (LED_BUILTIN, OUTPUT) ;
  Serial.begin (baudrate) ;
  while (!Serial) {
    delay (50) ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
  Serial.println ("Initiate CAN settings") ;
  //setCANRootClock (ACAN_CAN_ROOT_CLOCK::CLOCK_24MHz, 64) ; // Call if BEFORE any ACAN_T4_Settings instanciation
  ACAN_T4_Settings settings (bitrate) ; // 250 kbit/s
  const uint32_t errorCode = ACAN_T4::can1.begin (settings) ;

  Serial.print ("Bitrate prescaler: ") ;
  Serial.println (settings.mBitRatePrescaler) ;
  Serial.print ("Propagation Segment: ") ;
  Serial.println (settings.mPropagationSegment) ;
  Serial.print ("Phase segment 1: ") ;
  Serial.println (settings.mPhaseSegment1) ;
  Serial.print ("Phase segment 2: ") ;
  Serial.println (settings.mPhaseSegment2) ;
  Serial.print ("RJW: ") ;
  Serial.println (settings.mRJW) ;
  Serial.print ("Triple Sampling: ") ;
  Serial.println (settings.mTripleSampling ? "yes" : "no") ;
  Serial.print ("Actual bitrate: ") ;
  Serial.print (settings.actualBitRate ()) ;
  Serial.println (" bit/s") ;
  Serial.print ("Exact bitrate ? ") ;
  Serial.println (settings.exactBitRate () ? "yes" : "no") ; 
  Serial.print ("Distance from wished bitrate: ") ;
  Serial.print (settings.ppmFromWishedBitRate ()) ;
  Serial.println (" ppm") ;
  Serial.print ("Sample point: ") ;
  Serial.print (settings.samplePointFromBitStart ()) ;
  Serial.println ("%") ;
  if (0 == errorCode) {
    Serial.println ("can1 ok") ;
  }else{
    Serial.print ("Error can1: 0x") ;
    Serial.println (errorCode, HEX) ;
    while (1) {
      delay (5000) ;
      Serial.println ("Invalid setting") ;   
      digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
    }
  }
}

void Sense_can :: IMU_low(float data[2], int addr, uint32_t timebuff ){
  // create canmessage instance
  CANMessage IMU_low_msg;
  if (timebuff <= millis()){
    IMU_low_msg.id = addr; 
    IMU_low_msg.len = 8;
    IMU_low_msg.data32[0] = data[0]; //pitch 
    IMU_low_msg.data32[1] = data[1]; //roll
  }

  const bool check = ACAN_T4::can1.tryToSend(IMU_low_msg); //send message
  if (check){
    Serial.print("Pitch: ");
    Serial.printf("%x ", IMU_low_msg.data32[0]);
    Serial.println("Roll: ");
    Serial.printf("%x ", IMU_low_msg.data32[1]);
  }
}

void Sense_can :: IMU_hi_depth(float data[2], int addr, uint32_t timebuff){
  //create canmessage instance
  CANMessage IMU_hi_depth_msg;

  if (timebuff <= millis()){
    IMU_hi_depth_msg.id = addr; 
    IMU_hi_depth_msg.len = 8;
    IMU_hi_depth_msg.data32[0] = data[0]; //depth
    IMU_hi_depth_msg.data32[1] = data[1]; //yaw
  }

  const bool check = ACAN_T4::can1.tryToSend(IMU_hi_depth_msg); //send message
  if (check){
    Serial.print("Depth: ");
    Serial.printf("%x ", IMU_hi_depth_msg.data32[0]);
    Serial.println("Yaw: ");
    Serial.printf("%x ", IMU_hi_depth_msg.data32[1]);
  }
}

void Sense_can :: Heartbeat(){
  CANMessage ping;
  ping.id = 0x30;
  ping.len = 1;
  ping.data[0] = 0x10;
  const bool check = ACAN_T4::can1.tryToSend(ping);
  if (check){
    Serial.println("Sent successfully");
  }
  if(ACAN_T4::can1.receive(ping)){
    Serial.println("Received successfully");
  }
}
