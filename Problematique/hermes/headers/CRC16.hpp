#ifndef CRC16_HPP
#define CRC16_HPP

#include <stdint.h>

class CRC16 {
private:
    uint16_t m_Polynomial;

    uint16_t m_Value;

public:
    CRC16();

    uint16_t calculate(const uint8_t *data, uint16_t size);

};
#endif // CRC16_HPP