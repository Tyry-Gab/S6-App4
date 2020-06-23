/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "ICommunicationHandler.hpp"
#include "Particle.h"

class ManchesterCommunicationHandler : public ICommunicationHandler {
    private:
    uint8_t m_TXPin;
    uint8_t m_RXPin;
    Timer m_Timer;
    

    uint8_t m_BitToSend;
    bool m_HasSent;
    uint8_t m_ReveivingBuffer[80U];

    volatile uint8_t data;
    volatile bool m_isReceiving;
    

    enum state {
        AWAITING    = 0U,
        SETTING     = 1U,
        READING     = 2U,
        DONE        = 3U
    } volatile m_State, m_NextState;  
    
    // probably add internal functions to decode and encode bytes into manchester sequence
    

    public:
    void execute();
    ManchesterCommunicationHandler();
    ManchesterCommunicationHandler(uint8_t p_TXPin, uint8_t p_RXPin);

    // ICommunicationHandler
    void sendByte(uint8_t byte);
    void sendBytes(uint8_t* bytes, uint32_t size);
    void receiveByte(uint8_t* byte);
    void receiveBytes(uint8_t* bytes, uint32_t size);
    void onReceive();
    void receive();
};