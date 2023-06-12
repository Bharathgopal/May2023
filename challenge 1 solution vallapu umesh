#include <stdio.h>

typedef struct {
    unsigned int checksum;
} DataPacket;

unsigned int calculateChecksum(const DataPacket* packet) {
    unsigned int checksum = 0;
    const unsigned char* ptr = (const unsigned char*)packet;

    for (size_t i = 0; i < sizeof(DataPacket); ++i) {
        checksum += *ptr++;
    }

    return checksum;
}


int isPacketCorrupted(const DataPacket* packet) {
    unsigned int calculatedChecksum = calculateChecksum(packet);

    
    if (calculatedChecksum == packet->checksum) {
        return 0;  
    } else {
        return 1; 
    }
}

int main() {
    DataPacket packet;
    packet.checksum = calculateChecksum(&packet);
    if (isPacketCorrupted(&packet)) {
        printf("Packet is corrupted\n");
    } else {
        printf("Packet is not corrupted\n");
    }

    return 0;
}
