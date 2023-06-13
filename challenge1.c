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

// Check if the data packet is corrupted
bool isPacketCorrupted(const data_packet_t *packet) {
    uint16_t checksum = packet->id + packet->data_length;

    for (int i = 0; i < packet->data_length; i++) {
        checksum += packet->data[i];
    }

    return (checksum != packet->crc);
}

int main() {
    // Example usage
    data_packet_t packet = {1, 5, {10, 20, 30, 40, 50}, 0};

    // Calculate checksum
    for (int i = 0; i < packet.data_length; i++) {
        packet.crc += packet.data[i];
    }

    // Simulate corruption
    packet.data[2] = 35;

    // Check if the packet is corrupted
    printf("Packet is %s corrupted.\n", (isPacketCorrupted(&packet)) ? "" : "not");

    return 0;
}
