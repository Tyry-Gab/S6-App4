/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "../headers/ManchesterCommunicationHandler.hpp"
#include "Particle.h"

/*******************************************************************/
ManchesterCommunicationHandler::ManchesterCommunicationHandler(): m_Timer(500, &ManchesterCommunicationHandler::execute, *this) {
    m_Timer.start();
    m_isReceiving = false;
}

/*******************************************************************/
ManchesterCommunicationHandler::ManchesterCommunicationHandler(uint8_t p_TXPin, uint8_t p_RXPin): m_Timer(100, &ManchesterCommunicationHandler::execute, *this){
    m_Timer.start();
    m_TXPin = p_TXPin;
    // Pin qui transmet reste à High par défaut.
    pinSetFast(m_TXPin);

    m_RXPin = p_RXPin;
    m_isReceiving = false;
    clockState = false;
    attachInterrupt(m_RXPin, &ManchesterCommunicationHandler::onReceive, this, CHANGE);
    m_State = AWAITING;
    m_NextState = AWAITING;

    lastCount = 0;

    data = 0x0;
}

/*******************************************************************/
void ManchesterCommunicationHandler::sendByte(uint8_t byte) {
    WITH_LOCK(Serial) {
        Serial.printlnf("Sending byte %d", byte);
    }
    
    uint8_t mask = 0x80;
    for (int i = 7; i >= 0; i--) {
        uint8_t bit = byte & mask;
        bit >>= i;  
        /*WITH_LOCK(Serial) {
            //Serial.printf("%d%d ", bit, bit ^ 0x1);
        }*/
        
        m_BitToSend = bit;
        m_HasSent = false;
        while(!m_HasSent){
            os_thread_yield();
        }

        m_BitToSend = bit ^ 0x1;
        m_HasSent = false;
        while(!m_HasSent){
            os_thread_yield();
        }

        mask >>= 1U;
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
    clockState = !clockState;
    lastCount++;
    
    if (lastCount > 3)
    {
        m_State = AWAITING;        
    }

    delay(1);

    if(m_BitToSend){
        pinSetFast(m_TXPin);
    }
    else {
        pinResetFast(m_TXPin);
    }
    m_HasSent = true;


    /*if(m_isReceiving) {
        data ^= 0x1;
        WITH_LOCK(Serial) {
            Serial.printf("%d", data);
        }
    } */
    
}

/*******************************************************************/
void ManchesterCommunicationHandler::onReceive() {
    switch (m_State)
    {
    case AWAITING:
        data = !clockState;
        m_State = READING;
        lastCount = 0;
        break;

    case READING:
        if (clockState == data) {
            WITH_LOCK(Serial) {
                Serial.printf("%d", digitalRead(m_RXPin) ^ 0x1U);
            }
            lastCount = 0;
        }
        break;
    
    default:
        break;
    } 
}

/*******************************************************************/
void ManchesterCommunicationHandler::receive() {
            
}
