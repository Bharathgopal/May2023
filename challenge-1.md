# Data Packet Corruption Detection
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

uint16_t calculate_crc(const uint8_t *data, size_t length) {
    uint16_t crc = 0xFFFF;  // Initial CRC value

    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 0x0001)
                crc = (crc >> 1) ^ 0xA001;  // XOR with the CRC-16 polynomial
            else
                crc >>= 1;
        }
    }

    return crc;
}

int is_packet_corrupted(const data_packet_t *packet) {
    uint16_t calculated_crc = calculate_crc(packet->data, packet->data_length);

    if (calculated_crc != packet->crc)
        return 1;  // Packet is corrupted
    else
        return 0;  // Packet is not corrupted
}
