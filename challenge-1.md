#include <stdio.h>
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

uint16_t calculateCRC(const uint8_t *data, uint8_t length) {
    uint16_t crc = 0xFFFF;  // Initialize CRC with 0xFFFF

    for (int i = 0; i < length; i++) {
        crc ^= (uint16_t)data[i] << 8;  // XOR the byte with the CRC

        for (int j = 0; j < 8; j++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;  // If MSB is 1, shift left and XOR with polynomial
            } else {
                crc = crc << 1;  // If MSB is 0, just shift left
            }
        }
    }

    return crc;
}

int isPacketCorrupted(const data_packet_t *packet) {
    // Calculate the CRC of the packet data
    uint16_t calculatedCRC = calculateCRC(packet->data, packet->data_length);

    // Compare the calculated CRC with the packet's CRC
    if (calculatedCRC == packet->crc) {
        return 0;  // Packet is not corrupted
    } else {
        return 1;  // Packet is corrupted
    }
}

int main() {
    // Example 1: Valid Packet
    data_packet_t validPacket;
    validPacket.id = 1;
    validPacket.data_length = 4;
    validPacket.data[0] = 0x12;
    validPacket.data[1] = 0x34;
    validPacket.data[2] = 0x56;
    validPacket.data[3] = 0x78;
    validPacket.crc = calculateCRC(validPacket.data, validPacket.data_length);

    int isCorrupted = isPacketCorrupted(&validPacket);

    if (isCorrupted) {
        printf("Valid Packet is corrupted.\n");
    } else {
        printf("Valid Packet is not corrupted.\n");
    }

    // Example 2: Corrupted Packet
    data_packet_t corruptedPacket;
    corruptedPacket.id = 2;
    corruptedPacket.data_length = 4;
    corruptedPacket.data[0] = 0x12;
    corruptedPacket.data[1] = 0x34;
    corruptedPacket.data[2] = 0x56;
    corruptedPacket.data[3] = 0x78;
    corruptedPacket.crc = calculateCRC(corruptedPacket.data, corruptedPacket.data_length);

    // Introduce corruption by modifying one data byte
    corruptedPacket.data[2] = 0xAB;

    isCorrupted = isPacketCorrupted(&corruptedPacket);

    if (isCorrupted) {
        printf("Corrupted Packet is corrupted.\n");
    } else {
        printf("Corrupted Packet is not corrupted.\n");
    }

    return 0;
