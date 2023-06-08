#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)
typedef struct data_packet_t{
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
}data_packet_t;

uint16_t calculateCRC(const uint8_t* data, uint8_t length) {
    const uint16_t polynomial = 0xA001; // Standard polynomial
    uint16_t crc = 0xFFFF;

    for (uint8_t i = 0; i < length; ++i) {
        crc ^= data[i];

        for (uint8_t j = 0; j < 8; ++j) {
            if ((crc & 0x0001) != 0) {
                crc >>= 1;
                crc ^= polynomial;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

int isPacketCorrupted(const data_packet_t* packet) {
    // Calculate CRC for the packet data
    uint16_t calculatedCRC = calculateCRC(packet->data, packet->data_length);

    // Compare calculated CRC with the packet's stored CRC
    if (calculatedCRC == packet->crc) {
        return 0; 
    } else {
        return 1;
    }
}

