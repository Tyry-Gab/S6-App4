/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#include "../headers/Factory.hpp"

/*******************************************************************/
Factory::Factory() {

}

/*******************************************************************/
ManchesterCommunicationHandler* Factory::createHandler1() {
    static bool s_Created = false;
    static ManchesterCommunicationHandler s_ManchesterCommunicationHandler;

    if(!s_Created) {
        new (&s_ManchesterCommunicationHandler) ManchesterCommunicationHandler();

        s_Created = true;
    }

    return &s_ManchesterCommunicationHandler;
}