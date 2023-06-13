#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define MAX_PACKET_DATA_LENGTH (50)
typedef struct data_packet_t 
{
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;
uint16_t calculateChecksum(const data_packet_t *packet) 
{
    uint16_t checksum = packet->id + packet->data_length;
    for (int i = 0; i < packet->data_length; i++) 
    {
        checksum += packet->data[i];
    }
    return checksum;
}
bool isPacketCorrupted(const data_packet_t *packet) 
{
    uint16_t expectedChecksum = calculateChecksum(packet);
    return (expectedChecksum != packet->crc);
}
int main() 
{
    data_packet_t packet = {1, 5, {10, 20, 30, 40, 50}, 0};
    packet.crc = calculateChecksum(&packet);
    packet.data[2] = 35;
    if (isPacketCorrupted(&packet)) 
    {
        printf("Packet is corrupted.\n");
    } 
    else 
    {
        printf("Packet is not corrupted.\n");
    }
    return 0;
}