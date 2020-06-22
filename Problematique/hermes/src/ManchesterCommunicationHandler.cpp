/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "../headers/ManchesterCommunicationHandler.hpp"
#include "Particle.h"

/*******************************************************************/
ManchesterCommunicationHandler::ManchesterCommunicationHandler() {
    
}

/*******************************************************************/
ManchesterCommunicationHandler::ManchesterCommunicationHandler(uint8_t p_TXPin, uint8_t p_RXPin, Timer* p_Timer) {

}

/*******************************************************************/
void ManchesterCommunicationHandler::sendByte(uint8_t byte) {
    Serial.printlnf("Sending byte %d", byte);
}

/*******************************************************************/
void ManchesterCommunicationHandler::sendBytes(uint8_t* bytes, uint32_t size) {

}

/*******************************************************************/
void ManchesterCommunicationHandler::receiveByte(uint8_t* byte) {

}

/*******************************************************************/
void ManchesterCommunicationHandler::receiveBytes(uint8_t* bytes, uint32_t size) {

}