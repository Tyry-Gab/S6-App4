#include "../headers/CRC16.hpp"

/*******************************************************************/
CRC16::CRC16() {
    m_Polynomial = 0x4F69;
}


/*******************************************************************/
uint16_t CRC16::calculate(const uint8_t *p_Data, uint16_t p_Size) {
    unsigned char x;
    unsigned short crc = 0xFFFF;

    while (p_Size--){
        x = crc >> 8 ^ *p_Data++;
        x ^= x>>4;
        crc = (crc << 8) ^ ((unsigned short)(x << 12)) ^ ((unsigned short)(x <<5)) ^ ((unsigned short)x);
    }
    return crc;
}