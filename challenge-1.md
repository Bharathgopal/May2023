# Data Packet Corruption Detection
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t{
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

// CRC algorithm implementation (example)
uint16_t calculateCRC(uint8_t* data, uint8_t length) {
    uint16_t crc = 0xFFFF;  // Initial CRC value
    
    for (uint8_t i = 0; i < length; i++) {
        crc ^= (uint16_t)data[i] << 8;  // XOR CRC with next data byte
        
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;  // Polynomial: x^16 + x^12 + x^5 + 1
            } else {
                crc <<= 1;  // Shift left by 1
            }
        }
    }
    
    return crc;
}

// Verify if a data packet is corrupted
int isPacketCorrupted(data_packet_t* packet) {
    uint16_t calculatedCRC = calculateCRC(packet->data, packet->data_length);
    
    return (calculatedCRC == packet->crc) ? 0 : 1;  // Return 0 if not corrupted, 1 if corrupted
}
