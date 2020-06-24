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
    /*uint8_t i;
    uint16_t data;
    uint16_t crc = 0xffff;

    if (p_Size == 0)
        return (~crc);

    do
    {
        for (i=0, data=(uint16_t)0xff & *p_Data++;
                i < 8; 
                i++, data >>= 1)
        {
                if ((crc & 0x0001) ^ (data & 0x0001))
                    crc = (crc >> 1) ^ m_Polynomial;
                else  crc >>= 1;
        }
    } while (--p_Size);

    crc = ~crc;
    data = crc;
    crc = (crc << 8) | (data >> 8 & 0xff);

    return (crc);*/
}