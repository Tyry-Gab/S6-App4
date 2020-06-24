/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "ManchesterCommunicationHandler.hpp"
#include "CRC16.hpp"

class Factory {
    private:

    public:
    Factory();

    ManchesterCommunicationHandler* createHandler1();
    ManchesterCommunicationHandler* createHandler2();
    CRC16* createCRC16();

};

#endif // FACTORY_HPP