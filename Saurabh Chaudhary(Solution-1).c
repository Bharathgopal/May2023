#include <stdio.h>
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;


uint16_t calculateCRC(data_packet_t packet) {
    uint16_t crc = 0xFFFF; 
    
    crc ^= packet.id;
    crc ^= packet.data_length;

    for (int i = 0; i < packet.data_length; i++) {
        crc ^= packet.data[i];

        for (int j = 0; j < 8; j++) {
            if (crc & 0x0001)
                crc = (crc >> 1) ^ 0xA001;
            else
                crc = (crc >> 1);
        }
    }

    return crc;
}

int isPacketCorrupted(data_packet_t packet) {
    uint16_t recalculatedCRC = calculateCRC(packet);
    
    if (recalculatedCRC == packet.crc)
        return 0;
    else
        return 1;
}

int main() {
    data_packet_t packet;
    
    // Enter the ID: ;
    scanf("%hhu", &packet.id);
    
    // Enter the data length;
    scanf("%hhu", &packet.data_length);
    
    // Enter the data up to %d characters: MAX_PACKET_DATA_LENGTH;
    scanf("%s", packet.data);
    
    // Enter the CRC:
    scanf("%hu", &packet.crc);

    int isCorrupted = isPacketCorrupted(packet);

    if (isCorrupted)
        printf("Packet is corrupted.\n");
    else
        printf("Packet is not corrupted.\n");

    return 0;
}
