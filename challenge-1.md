# Data Packet Corruption Detection
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

// CRC lookup table (precomputed for CRC-16/CCITT)
static const uint16_t crc_table[256] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    // Rest of the CRC table...
};

uint16_t calculate_crc(const uint8_t* data, uint8_t length) {
    uint16_t crc = 0;

    for (uint8_t i = 0; i < length; ++i) {
        uint8_t index = ((crc >> 8) ^ data[i]) & 0xFF;
        crc = (crc << 8) ^ crc_table[index];
    }

    return crc;
}

int is_packet_corrupted(const data_packet_t* packet) {
    uint16_t calculated_crc = calculate_crc(packet->data, packet->data_length);
    return (calculated_crc != packet->crc);
}
