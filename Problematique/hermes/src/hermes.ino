/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "../headers/Factory.hpp"

uint8_t t;

ManchesterCommunicationHandler* test_Handler;


void setup() {
  Factory factory;
  Serial.begin(9600);
  test_Handler = factory.createHandler1();
}


void loop() {
  test_Handler->sendByte(0x7);

  delay(500);
}