/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/git/S6-App4/Problematique/Hermes/src/hermes.ino"
/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "../headers/Factory.hpp"

void setup();
void loop();
#line 8 "c:/git/S6-App4/Problematique/Hermes/src/hermes.ino"
SYSTEM_THREAD(ENABLED);

#define START_BYTE_0   (0x55U);
#define START_BYTE_1   (0x7EU);
#define TYPE_FLAGS     (0U);
#define END_BYTE       (0x7EU);

ManchesterCommunicationHandler* test_Handler1;
ManchesterCommunicationHandler* test_Handler2;
CRC16* test_CRC16;

uint8_t message[80U];

void setup() {
  Factory factory;
  Serial.begin(9600);
  test_Handler1 = factory.createHandler1();
  test_Handler2 = factory.createHandler2();
  test_CRC16 = factory.createCRC16();
  delay(100);

  message[0U] = START_BYTE_0;
  message[1U] = START_BYTE_1;
  message[2U] = TYPE_FLAGS;
  message[3U] = 73; // payload de 1 byte pour commencer
  for(int i = 4; i <= 76; i++){
    message[i] = i;
  }
  uint16_t crc = test_CRC16->calculate(&message[4U],73U);
  message[77U] = (crc >> 8) & 0xFF;
  message[78U] = crc & 0xFF;  
  message[79U] = END_BYTE;

  //Thread sending("sending", sendingThread);
  //Thread receiving("receiving", receivingThread);

  delay(1000);
}


void loop() {
  test_Handler1->sendBytes(message, 80);
  os_thread_yield();  
  pinSetFast(D7);
  delay(1000);
  test_Handler2->printReceivedData();
  delay(1000);
  WITH_LOCK(Serial) {
    Serial.printlnf(" ");
  }
}