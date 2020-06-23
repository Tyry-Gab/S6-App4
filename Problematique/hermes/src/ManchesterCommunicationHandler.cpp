/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "../headers/ManchesterCommunicationHandler.hpp"
#include "Particle.h"

/*******************************************************************/
ManchesterCommunicationHandler::ManchesterCommunicationHandler(): m_Timer(100, &ManchesterCommunicationHandler::execute, *this) {
    m_Timer.start();
}

/*******************************************************************/
ManchesterCommunicationHandler::ManchesterCommunicationHandler(uint8_t p_TXPin, uint8_t p_RXPin): m_Timer(100, &ManchesterCommunicationHandler::execute, *this) {
    m_Timer.start();
    m_TXPin = p_TXPin;
    m_RXPin = p_RXPin;
}

/*******************************************************************/
void ManchesterCommunicationHandler::sendByte(uint8_t byte) {
    WITH_LOCK(Serial) {
        Serial.printlnf("Sending byte %d", byte);
    }
    

    for (int i = 0; i<=7; i++) {
        uint8_t bit = byte & 0x01;

        WITH_LOCK(Serial) {
            Serial.printf("%d%d ", bit ^ 0x1, bit);
        }
        
        m_BitToSend = bit ^ 0x1;
        m_HasSent = false;
        while(!m_HasSent){
            os_thread_yield();
        }

        m_BitToSend = bit;
        m_HasSent = false;
        while(!m_HasSent){
            os_thread_yield();
        }

        byte >>= 0x1;
    }

    WITH_LOCK(Serial) {
        Serial.printf("\n\r");
    }
    
}

/*******************************************************************/
void ManchesterCommunicationHandler::sendBytes(uint8_t* bytes, uint32_t size) {
    for(uint32_t i = 0; i < size; i++) {
        sendByte(bytes[i]);
    }
}

/*******************************************************************/
void ManchesterCommunicationHandler::receiveByte(uint8_t* byte) {

}

/*******************************************************************/
void ManchesterCommunicationHandler::receiveBytes(uint8_t* bytes, uint32_t size) {

}

/*******************************************************************/
void ManchesterCommunicationHandler::execute() {
    WITH_LOCK(Serial) {
        //Serial.printlnf("Callback successfull");
    }
    if(m_BitToSend == 1U){
        pinSetFast(m_TXPin);
    }
    else {
        pinResetFast(m_TXPin);
    }
    m_HasSent = true;
}
