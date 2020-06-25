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
        pinMode(D6, INPUT_PULLUP);
        new (&s_ManchesterCommunicationHandler) ManchesterCommunicationHandler(D7, D6, createCRC16());
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
        pinMode(D5, INPUT_PULLUP);
        new (&s_ManchesterCommunicationHandler) ManchesterCommunicationHandler(D4, D5, createCRC16());
        s_Created = true;
    }

    return &s_ManchesterCommunicationHandler;
}

/*******************************************************************/
CRC16* Factory::createCRC16() {
    static bool s_Created = false;
    static CRC16 s_CRC16;
    if(!s_Created) {
        new (&s_CRC16) CRC16();
        s_Created = true;
    }
    return &s_CRC16;
}
