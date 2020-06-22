/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/git/S6-App4/Problématique/hermes/src/hermes.ino"
/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "../headers/Factory.hpp"

void setup();
void loop();
#line 8 "c:/git/S6-App4/Problématique/hermes/src/hermes.ino"
uint8_t t;

ManchesterCommunicationHandler* test_Handler;


void setup() {
  Factory factory;
  Serial.begin(9600);
  test_Handler = factory.createHandler1();
}


void loop() {
  test_Handler->sendByte(0x77);

  delay(100);

}