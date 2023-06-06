#include <stdio.h>
#include <stdint.h>
#define MAX_PACKET_DATA_LENGTH (50)
typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;                               
} data_packet_t;
int isPacketCorrupted(const data_packet_t* packet) {
    
    uint16_t calculated_crc = 0;
    for (int i = 0; i < packet->data_length; i++) {
        calculated_crc += packet->data[i];
    }
    
    return calculated_crc != packet->crc;
}
int main() {
    
    data_packet_t packet;
    packet.id = 0;
    packet.data_length = 20;
    for (int i = 0; i < packet.data_length; i++) {
        packet.data[i] = i + 1;
    }
    packet.crc = 100;
    if (isPacketCorrupted(&packet)) {
        
        printf("Packet is corrupted\n");
    } else {
       
        printf("Packet is not corrupted\n");
    }
    return 0;
}
