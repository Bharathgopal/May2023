#include <stdint.h>
#include <stdbool.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

// Function to calculate CRC
uint16_t calculateCRC(const data_packet_t* packet) {
    uint16_t crc = 0xFFFF; // Initial CRC value

    crc ^= packet->id; // XOR with packet ID
    crc ^= packet->data_length; // XOR with packet data length

    // XOR with packet data
    for (int i = 0; i < packet->data_length; i++) {
        crc ^= packet->data[i];
    }

    return crc;
}

// Function to verify CRC
bool verifyCRC(const data_packet_t* packet) {
    return packet->crc == calculateCRC(packet);
}