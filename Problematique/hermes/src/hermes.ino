/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "../headers/Factory.hpp"

SYSTEM_THREAD(ENABLED);

#define START_BYTE_0   (0x55U);
#define START_BYTE_1   (0x7EU);
#define TYPE_FLAGS     (0x00U);
#define END_BYTE       (0x7EU);

ManchesterCommunicationHandler* test_Handler1;
ManchesterCommunicationHandler* test_Handler2;
CRC16* test_CRC16;

uint8_t message[80U];
system_tick_t lastTimeSent;
system_tick_t lastTimeReceived;

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
  message[3U] = 17; // payload de 1 byte pour commencer
  for(int i = 4; i <= 20; i++){
    message[i] = i;
  }
  uint16_t crc = test_CRC16->calculate(&message[4U],17U);
  message[21U] = (crc >> 8) & 0xFF;
  message[22U] = crc & 0xFF;  
  message[23U] = END_BYTE;

  

  delay(1000);
  Thread receiving("receiving", receivingThread);
  Thread sending("sending", sendingThread);
}


void loop() {
}

void sendingThread(){
  while(true) {
    test_Handler1->sendBytes(message, 24);
    pinSetFast(D7);
    delay(1000);
  }
}

void receivingThread() {
  while (true)
  {
    test_Handler2->printReceivedData();
    delay(1000);
  }
  
}


// For reference
void standard(){
  while(true) {
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
}