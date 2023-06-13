#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

uint16_t crc16(uint8_t *data, uint8_t length) {
    uint16_t crc = 0xFFFF;
    uint8_t i, j;
    
    for (i = 0; i < length; ++i) {
        crc ^= data[i];
        for (j = 0; j < 8; ++j) {
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


int isPacketCorrupted(data_packet_t packet) { // Function to check if a data packet is corrupted

    uint16_t calculatedCRC = crc16((uint8_t*)&packet.id, sizeof(packet.id) + sizeof(packet.data_length) + packet.data_length);  // Calculate the CRC for the packet data
    
    return (calculatedCRC != packet.crc); // Compare the calculated CRC with the received CRC
}