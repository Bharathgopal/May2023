/******************************************************************************

// In this code, the Packet is Corrupted function calculates the CRC (Cyclic Redundancy Check).

// for the packet data by summing up all the bytes in the data array.

// It then compares the calculated CRC with the value stored in the crc field of the packet.

// If the two values don't match, it indicates that the packet is corrupted.

// You can call the Packet is Corrupted function for each received packet to check 

// if it is corrupted before further processing or handling it accordingly.




#include <stdio.h>
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;                               // CRC (Cyclic Redundancy Check)
} data_packet_t;

int isPacketCorrupted(const data_packet_t* packet) {
    // Calculate CRC for the packet data
    uint16_t calculated_crc = 0;
    for (int i = 0; i < packet->data_length; i++) {
        calculated_crc += packet->data[i];
    }

    // Compare calculated CRC with the packet's CRC field
    return calculated_crc != packet->crc;
}

int main() {
    // Example usage
    data_packet_t packet;
    packet.id = 1;
    packet.data_length = 10;
    for (int i = 0; i < packet.data_length; i++) {
        packet.data[i] = i + 1;
    }
    packet.crc = 55;

    if (isPacketCorrupted(&packet)) {
        // Packet is corrupted
        printf("Packet is corrupted\n");
    } else {
        // Packet is not corrupted
        printf("Packet is not corrupted\n");
    }

    return 0;
}
