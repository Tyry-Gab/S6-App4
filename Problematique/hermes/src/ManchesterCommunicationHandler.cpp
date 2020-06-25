/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "../headers/ManchesterCommunicationHandler.hpp"
#include "Particle.h"

#define START_BYTE_0   (0x55U)
#define START_BYTE_1   (0x7EU)
#define TYPE_FLAGS     (0U)
#define END_BYTE       (0x7EU)

/*******************************************************************/
ManchesterCommunicationHandler::ManchesterCommunicationHandler(): m_Timer(2, &ManchesterCommunicationHandler::execute, *this) {
    m_isReceiving = false;
}

/*******************************************************************/
ManchesterCommunicationHandler::ManchesterCommunicationHandler(uint8_t p_TXPin, uint8_t p_RXPin, CRC16* p_CRC16): m_Timer(2, &ManchesterCommunicationHandler::execute, *this){
    m_Timer.start();
    m_TXPin = p_TXPin;
    // Pin qui transmet reste à High par défaut.
    pinSetFast(m_TXPin);

    m_RXPin = p_RXPin;
    m_isReceiving = false;
    clockState = false;
    attachInterrupt(m_RXPin, &ManchesterCommunicationHandler::onReceive, this, CHANGE);
    m_State = AWAITING;

    lastCount = 0;

    data = 0x0;

    m_IsDataReady = false;

    m_ReceivedCount = 0U;
    m_WritingHead = 0U;
    m_HasNewByte = false;
    m_CRC16 = p_CRC16;
}

/*******************************************************************/
void ManchesterCommunicationHandler::sendByte(uint8_t byte) {
    
    uint8_t mask = 0x80;
    for (int i = 7; i >= 0; i--) {
        uint8_t bit = byte & mask;
        bit >>= i;  
        
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
    
}


/*******************************************************************/
void ManchesterCommunicationHandler::sendBytes(uint8_t* bytes, uint32_t size) {
    for(uint32_t i = 0; i < size; i++) {
        sendByte(bytes[i]);
    }
}

/*******************************************************************/
void ManchesterCommunicationHandler::execute() {
    clockState = !clockState;
    if (digitalRead(m_RXPin) == 0x1U)
        lastCount = lastCount + 1;
    else 
        lastCount = 0;
    
    if (lastCount > 3)
    {
        m_State = AWAITING;
        m_WritingHead = 0U;  
        m_ReceivedByte = 0U;   
        m_ReceivedCount = 0;   
    }

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
        m_State = PREAMBULE;
        break;

    case PREAMBULE:
        if (clockState == data) {          
            m_ReceivedByte <<= 1U;
            m_ReceivedByte |= digitalRead(m_RXPin) ^ 0x1U;
            if(m_ReceivedCount != 7U){
                m_ReceivedCount++;
            } 
            else {
                if (m_ReceivedByte != START_BYTE_0){
                    m_State = ERROR;
                } else {
                    m_State = START;
                }
                m_ReceivedCount = 0U;
                m_ReceivedByte = 0;
            }
        }
        break;

    case START:
        if (clockState == data) {          
            m_ReceivedByte <<= 1U;
            m_ReceivedByte |= digitalRead(m_RXPin) ^ 0x1U;                
            if(m_ReceivedCount != 7U){
                m_ReceivedCount++;
            } 
            else {
                if (m_ReceivedByte != START_BYTE_1){
                    m_State = ERROR;
                } else {
                    m_State = TYPE_FLAG;
                }
                m_ReceivedCount = 0U;
                m_ReceivedByte = 0;
            }
        }
        break;

    case TYPE_FLAG:
        if (clockState == data) {          
            m_ReceivedByte <<= 1U;
            m_ReceivedByte |= digitalRead(m_RXPin) ^ 0x1U;                
            if(m_ReceivedCount != 7U){
                m_ReceivedCount++;
            } 
            else {
                if (m_ReceivedByte != TYPE_FLAGS){
                    m_State = ERROR;
                } else {
                    m_State = LENGTH;
                }
                m_ReceivedCount = 0U;
                m_ReceivedByte = 0;
            }
        }
        break;

    case LENGTH:
        if (clockState == data) {          
            m_ReceivedByte <<= 1U;
            m_ReceivedByte |= digitalRead(m_RXPin) ^ 0x1U;                
            if(m_ReceivedCount != 7U){
                m_ReceivedCount++;
            } 
            else {
                m_State = READING;  
                m_IsDataReady = false;  
                m_MessageLength = m_ReceivedByte;
                m_ReadingByteCounter = 0;            
                m_ReceivedCount = 0U;
                m_ReceivedByte = 0;
            }
        }
        break;

    case READING:
        if (clockState == data) {          
            m_ReceivedByte <<= 1U;
            m_ReceivedByte |= digitalRead(m_RXPin) ^ 0x1U;                
            if(m_ReceivedCount != 7U){
                m_ReceivedCount++;
            } 
            else {
                m_ReceivingBuffer[m_WritingHead++] = m_ReceivedByte;
                ++m_ReadingByteCounter;
                if (m_ReadingByteCounter == m_MessageLength) {
                    m_CrcReceived = 0x0000;
                    m_State = CRC;            
                }
                m_ReceivedCount = 0U;
                m_ReceivedByte = 0;
            }
        }
        break;

    case CRC:
        if (clockState == data) {          
            m_CrcReceived <<= 1U;
            m_CrcReceived |= digitalRead(m_RXPin) ^ 0x1U;                
            if(m_ReceivedCount != 15U){
                m_ReceivedCount++;
            } 
            else {
                m_State = END;
                m_ReceivedCount = 0U;
            }
        }
        break;

    case END:
        if (clockState == data) {          
            m_ReceivedByte <<= 1U;
            m_ReceivedByte |= digitalRead(m_RXPin) ^ 0x1U;                
            if(m_ReceivedCount != 7U){
                m_ReceivedCount++;
            } 
            else {
                if (m_ReceivedByte != END_BYTE){
                    m_State = ERROR;
                } else {
                    m_IsDataReady = m_CRC16->calculate( (const_cast <uint8_t*> (m_ReceivingBuffer)) , m_MessageLength) == m_CrcReceived;            
                    m_WritingHead = 0U; 
                }
                m_ReceivedCount = 0U;
                m_ReceivedByte = 0;
            }
        }
        break;

    case ERROR:
        break;
    default:
        break;
    }     
}

/*******************************************************************/
void ManchesterCommunicationHandler::receive() {
            
}

/******************************************************************/
void ManchesterCommunicationHandler::printReceivedData() {
    if (m_IsDataReady) {
        WITH_LOCK(Serial) {
            Serial.println("Data received: ");            
        }
        for (int i = 0; i < m_MessageLength; i++)
        {
            WITH_LOCK(Serial) {
                Serial.printlnf("%d", m_ReceivingBuffer[i]);
            }
        }
        
    }
    else {
        WITH_LOCK(Serial) {
            Serial.printlnf("No data received...");
        }
    }
}
