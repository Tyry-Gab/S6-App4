/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "ICommunicationHandler.hpp"
#include "CRC16.hpp"
#include "Particle.h"

class ManchesterCommunicationHandler : public ICommunicationHandler {
    private:
    uint8_t m_TXPin;
    uint8_t m_RXPin;
    Timer m_Timer;
    
    volatile bool clockState;
    int lastCount;
    volatile uint8_t m_ReceivedCount;
    volatile uint8_t m_WritingHead;
    volatile uint8_t m_ReceivedByte;
    volatile uint8_t m_ReceivingBuffer[73U];
    volatile bool m_HasSent;
    uint8_t m_BitToSend;

    volatile bool data;
    volatile bool m_isReceiving;

    volatile uint8_t m_ReadingByteCounter;
    volatile uint8_t m_MessageLength;

    volatile uint16_t m_CrcReceived;

    volatile bool m_IsDataReady;
    
    CRC16* m_CRC16;

    enum state {
        AWAITING    = 0U,
        PREAMBULE   = 1U,
        START       = 2U,
        TYPE_FLAG   = 3U,
        LENGTH      = 4U,
        READING     = 5U,
        CRC         = 6U,
        END         = 7U,
        ERROR       = 8U
    } volatile m_State;  
    
    

    public:
    void execute();
    ManchesterCommunicationHandler();
    ManchesterCommunicationHandler(uint8_t p_TXPin, uint8_t p_RXPin, CRC16* p_CRC16);

    // ICommunicationHandler
    void sendByte(uint8_t byte);
    void sendBytes(uint8_t* bytes, uint32_t size);
    void onReceive();
    void receive();
    void printReceivedData();
};