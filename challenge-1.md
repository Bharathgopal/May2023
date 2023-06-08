# Data Packet Corruption Detection
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

uint16_t calculate_crc(const data_packet_t* packet) {
    uint16_t crc = 0;
    
    // Calculate CRC over the packet fields excluding crc
    uint8_t* ptr = (uint8_t*)packet;
    size_t size = sizeof(data_packet_t) - sizeof(uint16_t);
    for (size_t i = 0; i < size; ++i) {
        crc ^= (uint16_t)(*ptr++) << 8;
        for (uint8_t bit = 0; bit < 8; ++bit) {
            if (crc & 0x8000)
                crc = (crc << 1) ^ 0x1021;
            else
                crc <<= 1;
        }
    }
    
    return crc;
}

int is_packet_corrupted(const data_packet_t* packet) {
    // Calculate the CRC for the received packet
    uint16_t received_crc = packet->crc;
    uint16_t calculated_crc = calculate_crc(packet);
    
    // Compare the calculated CRC with the received CRC
    if (received_crc == calculated_crc)
        return 0; // Packet is not corrupted
    else
        return 1; // Packet is corrupted
}
