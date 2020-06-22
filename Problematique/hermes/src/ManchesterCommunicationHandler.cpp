/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "../headers/ManchesterCommunicationHandler.hpp"
#include "Particle.h"

/*******************************************************************/
ManchesterCommunicationHandler::ManchesterCommunicationHandler() {
    new (m_Timer) Timer(100, &ManchesterCommunicationHandler::send, *this);
    m_Timer->start();
}

/*******************************************************************/
ManchesterCommunicationHandler::ManchesterCommunicationHandler(uint8_t p_TXPin, uint8_t p_RXPin) {
    new (m_Timer) Timer(100, &ManchesterCommunicationHandler::send, *this);
}

/*******************************************************************/
void ManchesterCommunicationHandler::sendByte(uint8_t byte) {
    Serial.printlnf("Sending byte %d", byte);

    for (int i = 0; i<=7; i++) {
        uint8_t bit = byte & 0x01;

        Serial.printf("%d%d ", bit ^ 0x1, bit);
        m_BitToSend = bit ^ 0x1;
        while(!m_HasSent);
        m_BitToSend = bit;

        byte >>= 0x1;
    }

    Serial.printf("\n\r");
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

/*******************************************************************/
void ManchesterCommunicationHandler::send() {
    Serial.printlnf("Callback successfull");
    if(m_BitToSend){
        pinSetFast(m_TXPin);
    }
    else {
        pinResetFast(m_TXPin);
    }
    m_HasSent = true;
}
