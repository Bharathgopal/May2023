// In this code, the Packet is Corrupted function calculates the CRC (Cyclic Redundancy Check).
// The code first calculates the CRC checksum for the data packet. 
// It then compares the calculated CRC checksum to the CRC checksum that is stored in the packet. 
// If the two checksums do not match, then the packet is corrupted.
// This code can be used to detect data corruption in any type of data transmission, including wireless communication, wired communication, and storage.
// This will print the following output:
//   Packet is not corrupted.
// If we want to test the code with a corrupted packet, we can change the value of the packet.data[i] variable to any value other than i. 
// For example, you could change the value of packet.data[0] to 255. 
// When we do this, the code will print the following output:
//   Packet is corrupted.
// For this the following source code is written below in C Language

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

uint16_t calculate_crc(data_packet_t *packet) 
{
  uint16_t crc = 0;
  for (int i = 0; i < packet->data_length; i++) 
  {
    crc = crc ^ packet->data[i];
  }
  return crc;
}

bool is_data_packet_corrupted(data_packet_t *packet) 
{
  uint16_t calculated_crc = calculate_crc(packet);
  if (calculated_crc != packet->crc) 
  {
    return true;
  }
  return false;
}

int main() 
{
  data_packet_t packet;
  packet.id = 1;
  packet.data_length = 10;
  for (int i = 0; i < 10; i++) 
  {
    packet.data[i] = i;
  }
  packet.crc = calculate_crc(&packet);

  printf("Packet is %scorrupted.\n", is_data_packet_corrupted(&packet) ? "":"not ");

  return 0;
}