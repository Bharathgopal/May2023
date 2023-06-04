// Solution using CRC-16 ALGORITHM
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

// CRC algorithm implementation
// function to calculate CRC
uint16_t calculate_crc(const uint8_t* data, uint8_t length) {
    uint16_t crc = 0xFFFF; //Initialization of crc to 0xFFFF

    for (uint8_t i = 0; i < length; i++) {
        crc ^= (uint16_t)data[i] << 8;

        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;  // Polynomial: x^16 + x^12 + x^5 + 1
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

// Method to check if a data packet is corrupted
int is_packet_corrupted(const data_packet_t* packet) {
    // Calculate the CRC of the received packet (excluding the crc field)
    uint16_t received_crc = packet->crc;
    packet->crc = 0;  // Set the crc field to zero before calculating CRC
    uint16_t calculated_crc = calculate_crc((const uint8_t*)packet, sizeof(data_packet_t));

    // Compare the calculated CRC with the received CRC
    if (received_crc == calculated_crc) {
        return 0;  // Packet is not corrupted
    } else {
        return 1;  // Packet is corrupted
    }
}
