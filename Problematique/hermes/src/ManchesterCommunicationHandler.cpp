/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "../headers/ManchesterCommunicationHandler.hpp"
#include "Particle.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

/*******************************************************************/
ManchesterCommunicationHandler::ManchesterCommunicationHandler(): m_Timer(5, &ManchesterCommunicationHandler::execute, *this) {
    m_isReceiving = false;
}

/*******************************************************************/
ManchesterCommunicationHandler::ManchesterCommunicationHandler(uint8_t p_TXPin, uint8_t p_RXPin): m_Timer(5, &ManchesterCommunicationHandler::execute, *this){
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

    m_ReceivedCount = 0U;
    m_WritingHead = 0U;
    m_HasNewByte = false;
}

/*******************************************************************/
void ManchesterCommunicationHandler::sendByte(uint8_t byte) {
    /*WITH_LOCK(Serial) {
        Serial.printlnf("Sending byte %d", byte);
    }*/
    
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

    /*WITH_LOCK(Serial) {
        Serial.printf("\n\r");
    }*/
    
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
        m_WritingHead = 0U;  
        m_ReceivedByte = 0U;   
        m_ReceivedCount = 0;   
    }

    delay(1);

    if(m_BitToSend){
        pinSetFast(m_TXPin);
    }
    else {
        pinResetFast(m_TXPin);
    }
    m_HasSent = true;

    if(m_HasNewByte){
        WITH_LOCK(Serial) {
            Serial.printlnf(" %d", m_ReceivingBuffer[m_WritingHead-1]);
        }
        m_HasNewByte = false;
    }
    
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
            m_ReceivedByte <<= 1U;
            m_ReceivedByte |= digitalRead(m_RXPin) ^ 0x1U;                
            if(m_ReceivedCount == 7U){
                m_HasNewByte = true;
                m_ReceivedCount = 0U;
                m_ReceivingBuffer[m_WritingHead++] = m_ReceivedByte;
                m_ReceivedByte = 0;
            }
            else {
                m_ReceivedCount++;
            } 
            lastCount = 0;
        }
        break;
    case DONE:
        m_WritingHead = 0U;  
        break;
    default:
        break;
    } 
}

/*******************************************************************/
void ManchesterCommunicationHandler::receive() {
            
}
