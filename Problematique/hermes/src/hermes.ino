/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "../headers/Factory.hpp"

SYSTEM_THREAD(ENABLED);

ManchesterCommunicationHandler* test_Handler;
uint8_t state = 0;

void setup() {
  Factory factory;
  Serial.begin(9600);
  test_Handler = factory.createHandler1();
  pinMode(D7, OUTPUT);
}


void loop() {
  test_Handler->sendByte(0x7);
  state ^= 1;
  //digitalWrite(D7, state);
  delay(500);
}