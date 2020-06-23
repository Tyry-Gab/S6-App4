/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "../headers/Factory.hpp"

SYSTEM_THREAD(ENABLED);

ManchesterCommunicationHandler* test_Handler1;
ManchesterCommunicationHandler* test_Handler2;

void setup() {
  Factory factory;
  Serial.begin(9600);
  test_Handler1 = factory.createHandler1();
  test_Handler2 = factory.createHandler2();
}


void loop() {
  test_Handler1->sendByte(0x7);
  os_thread_yield();
  pinSetFast(D7);
  delay(1000);
}