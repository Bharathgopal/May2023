#include <stdint.h>
#include <stdbool.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

#define CRC_POLYNOMIAL 0x1021

uint16_t calculateCRC(uint8_t* data, uint8_t length) {
    uint16_t crc = 0xFFFF;

    for (uint8_t i = 0; i < length; i++) {
        crc ^= (uint16_t)data[i] << 8;

        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x8000)
                crc = (crc << 1) ^ CRC_POLYNOMIAL;
            else
                crc <<= 1;
        }
    }

    return crc;
}

bool isPacketCorrupted(data_packet_t* packet) {
    uint16_t calculatedCRC = calculateCRC(packet->data, packet->data_length);
    return (calculatedCRC != packet->crc);
}

int main() {
    data_packet_t packet;
    packet.id = 1;
    packet.data_length = 15;
    packet.data[0] = 'A';
    packet.data[1] = 'D';
    packet.data[2] = 'I';
    packet.data[3] = 'T';
    packet.data[4] = 'H';
    packet.data[5] = 'Y ';
    packet.data[6] = 'A';
    packet.data[7] = ' ';
    packet.data[8] = 'H';
    packet.data[9] = '0';
    packet.data[10] = 'L';
    packet.data[11] = 'L';
    packet.data[12] = 'A';
    packet.crc = calculateCRC(packet.data, packet.data_length);

    bool isCorrupted = isPacketCorrupted(&packet);
    if (isCorrupted) {
        printf("Packet is corrupted.\n");
    } else {
        printf("Packet is not corrupted.\n");
    }

    return 0;
}
