#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

// Function to calculate the CRC
uint16_t calculateCRC(const uint8_t* data, size_t length) {
    uint16_t crc = 0xFFFF; // Initial CRC value

    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];

        for (int j = 0; j < 8; j++) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= 0xA001; // CRC-16 polynomial
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}

// Function to check if a data packet is corrupted
int isPacketCorrupted(const data_packet_t* packet) {
    uint16_t calculatedCRC = calculateCRC(packet->data, packet->data_length);

    return (calculatedCRC != packet->crc);
}
