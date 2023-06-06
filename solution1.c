#include <stdio.h>
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)
// Given data packet
typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

// CRC 16 Algorithm
uint16_t calculate_crc(const uint8_t *data, uint8_t length) {
    uint16_t crc = 0xFFFF;
    uint16_t polynomial = 0x1021;

    for (uint8_t i = 0; i < length; ++i) {
        crc ^= (uint16_t)(data[i] << 8);
        for (uint8_t j = 0; j < 8; ++j) {
            crc = (crc & 0x8000) ? ((crc << 1) ^ polynomial) : (crc << 1);
        }
    }

    return crc;
}

// Check if the data packet is corrupted
int is_packet_corrupted(const data_packet_t *packet) {
    uint16_t calculated_crc = calculate_crc(packet->data, packet->data_length);

    if (calculated_crc == packet->crc) {
        return 0; // Not corrupted
    } else {
        return 1; // Corrupted
    }
}

int main() {
    data_packet_t packet;
    packet.id = 1;
    packet.data_length = 5;
    packet.data[0] = 'H';
    packet.data[1] = 'e';
    packet.data[2] = 'l';
    packet.data[3] = 'l';
    packet.data[4] = 'o';
    packet.crc = calculate_crc(packet.data, packet.data_length);

    int is_corrupted = is_packet_corrupted(&packet);

    if (is_corrupted) {
        printf("Packet is corrupted.\n");
    } else {
        printf("Packet is not corrupted.\n");
    }

    return 0;
}
