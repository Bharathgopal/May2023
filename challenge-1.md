#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

// CRC-16 (CCITT) polynomial: x^16 + x^12 + x^5 + 1
const uint16_t crc16_table[] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF
};


uint16_t calculate_crc(const data_packet_t* packet) {
    uint16_t crc = 0;
    uint8_t i;

 crc ^= packet->id;
 crc ^= packet->data_length;

 for (i = 0; i < packet->data_length; i++) {
        uint8_t index = ((crc >> 8) ^ packet->data[i]) & 0xFF;
        crc = (crc << 8) ^ crc16_table[index];
    }

   return crc;
}

// Verify  data packet is corrupted
int is_packet_corrupted(const data_packet_t* packet) {
    uint16_t crc = calculate_crc(packet);
    return (crc != packet->crc);
}
