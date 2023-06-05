#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

uint16_t calculate_crc(const data_packet_t* packet) {
    uint16_t crc = 0xFFFF;
    
    crc ^= packet->id;
    crc ^= packet->data_length;

    for (int i = 0; i < packet->data_length; i++) {
        crc ^= packet->data[i];
        
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

int is_packet_corrupted(const data_packet_t* packet) {
    uint16_t calculated_crc = calculate_crc(packet);
    
    return (calculated_crc != packet->crc);
}