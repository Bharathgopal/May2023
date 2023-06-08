#include <stdio.h>
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

// CRC-16-CCITT polynomial: x^16 + x^12 + x^5 + 1
#define CRC16_POLY 0x1021

// Function to calculate the CRC value
uint16_t calculate_crc(const uint8_t *data, size_t length) {
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < length; ++i) {
        crc ^= data[i] << 8;
        for (uint8_t bit = 0; bit < 8; ++bit) {
            if (crc & 0x8000)
                crc = (crc << 1) ^ CRC16_POLY;
            else
                crc <<= 1;
        }
    }
    return crc;
}

// Function to check if a data packet is corrupted
int is_packet_corrupted(const data_packet_t *packet) {
    uint16_t calculated_crc = calculate_crc(packet->data, packet->data_length);
    return (packet->crc != calculated_crc);
}

int main() {
    // Example usage
    data_packet_t packet;
    packet.id = 1;
    packet.data_length = 10;
    packet.data[0] = 0x11;
    packet.data[1] = 0x22;
    packet.data[2] = 0x33;
    packet.data[3] = 0x44;
    packet.data[4] = 0x55;
    packet.data[5] = 0x66;
    packet.data[6] = 0x77;
    packet.data[7] = 0x88;
    packet.data[8] = 0x99;
    packet.data[9] = 0xAA;
    packet.crc = calculate_crc(packet.data, packet.data_length);

    // Introduce an error by modifying the data
    packet.data[4] = 0xCC;

    // Check if the packet is corrupted
    if (is_packet_corrupted(&packet)) {
        printf("Data packet is corrupted!\n");
    } else {
        printf("Data packet is valid.\n");
    }

    return 0;
}