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
        pinMode(D7, OUTPUT);
        pinMode(D6, INPUT);
        new (&s_ManchesterCommunicationHandler) ManchesterCommunicationHandler(D7, D6);
        s_Created = true;
    }

    return &s_ManchesterCommunicationHandler;
}

/*******************************************************************/
ManchesterCommunicationHandler* Factory::createHandler2() {
    static bool s_Created = false;
    static ManchesterCommunicationHandler s_ManchesterCommunicationHandler;

    if(!s_Created) {
        pinMode(D4, OUTPUT);
        pinMode(D5, INPUT);
        new (&s_ManchesterCommunicationHandler) ManchesterCommunicationHandler(D4, D5);
        s_Created = true;
    }

    return &s_ManchesterCommunicationHandler;
}
