/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "ManchesterCommunicationHandler.hpp"

class Factory {
    private:

    public:
    Factory();

    ManchesterCommunicationHandler* createHandler1();
    ManchesterCommunicationHandler* createHandler2();
};

#endif // FACTORY_HPP