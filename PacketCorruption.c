/*    *** Data Packet Corruption Detection ***

  In a Wireless communciation device, multiple data packets are transferred over the air.
  It is possible that data might get corrupted or lost before it reaches the destination.
  Create a method to identify if a data packet is corrupted
  Assume below format for the data packet  

*/
// Here i'm checking packet is corrupted are not.

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

bool isPacketCorrupted(const data_packet_t* packet) {
    uint16_t calculate = 0;

/** here we can use a cyclic redundancy check (CRC) algorithm,
    The CRC algorithm generates a checksum based on the packet data and stores it in the crc field of the data_packet_t structure. **/

    for (int i = 0; i < packet->data_length; i++) {
        calculate = packet->data[i] << 8; // the current data byte with the most significant 8 bits of the calculated CRC

    // Shift the calculated CRC left by 1 and XOR it with the polynomial

    // Compare the calculated CRC with the stored CRC
    return calculate != packet->crc;

int main() {
    // here i'm using Example usage for most understandable in main function.
    data_packet_t packet;
    packet.id = 1;
    packet.data_length = 5;
    packet.data[0] = 'H';
    packet.data[1] = 'e';
    packet.data[2] = 'l';
    packet.data[3] = 'l';
    packet.data[4] = 'o';
    packet.crc = 0x4B37;

    if (isPacketCorrupted(&packet)) {
        printf("The packet is corrupted.\n");
    } else {
        printf("The packet is not corrupted.\n");
    }

    return 0;
}
// The main function demonstrates an example usage of the isPacketCorrupted function with a sample packet.