#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t
{
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

uint16_t calculateCRC(data_packet_t *packet)
{
    uint16_t crc = 0xFFFF;        // Initial CRC value
    uint16_t polynomial = 0xA001; // CRC-16 polynomial

    // Calculate CRC over the packet's ID, data length, and data
    crc ^= packet->id;
    crc ^= packet->data_length;

    for (uint8_t i = 0; i < packet->data_length; i++)
    {
        crc ^= packet->data[i];

        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x0001)
            {
                crc = (crc >> 1) ^ polynomial;
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return crc;
}

// The isPacketCorrupted function returns true if the packet is corrupted (the calculated CRC doesn't match the received CRC) and false otherwise.

bool isPacketCorrupted(data_packet_t *receivedPacket)
{
    uint16_t calculatedCRC = calculateCRC(receivedPacket);
    return (calculatedCRC != receivedPacket->crc);
}
