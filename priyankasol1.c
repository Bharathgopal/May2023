Data Packet Corruption Detection
* In a Wireless communciation device, multiple data packets are transferred over the air. 
* It is possible that data might get corrupted or lost before it reaches the destination.
* Create a method to identify if a data packet is corrupted
* Assume below format for the data packet

```
#define MAX_PACKET_DATA_LENGTH (50)
typedef struct data_packet_t{
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
}data_packet_t;

--------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

uint16_t calculateCRC(const uint8_t *data, size_t length) {
    uint16_t crc = 0xFFFF;  
    
    for (size_t i = 0; i < length; i++) {
        crc ^= (uint16_t)data[i];  
        
        for (int j = 0; j < 8; j++) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= 0xA001;  
            } else {
                crc >>= 1;
            }
        }
    }
    
    return crc;
}

bool isPacketCorrupted(const data_packet_t *packet) {
    uint16_t crc = calculateCRC((const uint8_t *)packet, sizeof(data_packet_t) - sizeof(uint16_t));
    
    return (crc != packet->crc);
}

int main() {
    data_packet_t packet = {
        .id = 0x01,
        .data_length = 4,
        .data = {0x12, 0x34, 0x56, 0x78},
        .crc = 0x0000
    };

    packet.crc = calculateCRC((const uint8_t *)&packet, sizeof(data_packet_t) - sizeof(uint16_t));

    packet.data[2] = 0xAA;

    if (isPacketCorrupted(&packet)) {
        printf("Packet is corrupted.\n");
    } else {
        printf("Packet is not corrupted.\n");
    }

    return 0;
}