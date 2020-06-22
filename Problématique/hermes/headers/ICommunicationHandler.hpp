/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#ifndef ICOMMUNICATIONHANDLER_HPP
#define ICOMMUNICATIONHANDLER_HPP

#include <stdint.h>


class ICommunicationHandler {
private:

public:
    virtual void sendByte(uint8_t byte) = 0;
    virtual void sendBytes(uint8_t* bytes, uint32_t size) = 0;
    virtual void receiveByte(uint8_t* byte) = 0;
    virtual void receiveBytes(uint8_t* bytes, uint32_t size) = 0;
};

#endif // ICOMMUNICATIONHANDLER_HPP
