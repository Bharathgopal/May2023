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

// CRC-16 algorithm
uint16_t crc16(uint8_t *data, uint8_t length)
{
   uint16_t crc = 0xFFFF;
   uint8_t i, j;

   for (i = 0; i < length; i++)
   {
      crc ^= data[i];
      for (j = 0; j < 8; j++)
      {
         if (crc & 0x0001)
         {
            crc >>= 1;
            crc ^= 0xA001;
         }
         else
         {
            crc >>= 1;
         }
      }
   }

   return crc;
}

// Transmitter side
void transmit(data_packet_t packet)
{
   // Calculate and store the CRC checksum
   packet.crc = crc16(packet.data, packet.data_length);

   // Transmit the packet over the wireless channel
   printf("Transmitting data packet...\n");
   printf("Packet ID: %d\n", packet.id);
   printf("Data Length: %d\n", packet.data_length);
   printf("Data: ");
   for (uint8_t i = 0; i < packet.data_length; i++)
   {
      printf("%02X ", packet.data[i]);
   }
   printf("\nCRC: %04X\n", packet.crc);
   printf("Packet transmission complete.\n");
   printf("-----------------------------\n");
}

// Receiver side
bool receive(data_packet_t *packet)
{
   // Simulating received packet
   data_packet_t received_packet;
   received_packet.id = 1;
   received_packet.data_length = 10;
   received_packet.data[0] = 0x12;
   received_packet.data[1] = 0x34;
   received_packet.data[2] = 0x56;
   received_packet.data[3] = 0x78;
   received_packet.data[4] = 0x9A;
   received_packet.data[5] = 0xBC;
   received_packet.data[6] = 0xDE;
   received_packet.data[7] = 0xF0;
   received_packet.data[8] = 0x11;
   received_packet.data[9] = 0x22;

   /*The calculated CRC (0xFB31) does not match the received packet's CRC (0xABCD). Therefore, the data packet corruption status is marked as "Data packet corrupted!"*/

   received_packet.crc = 0xFB31; // Simulated received CRC
   // received_packet.crc = 0xABCD;

   // Verify the integrity of the received packet
   uint16_t calculated_crc = crc16(received_packet.data, received_packet.data_length);
   if (calculated_crc != received_packet.crc)
   {
      printf("Data packet corrupted! Discarding...\n");
      return false;
   }

   // Packet is valid, store the received packet
   *packet = received_packet;
   return true;
}

int main()
{
   // Create a data packet
   data_packet_t packet;
   packet.id = 1;
   packet.data_length = 10;
   packet.data[0] = 0x12;
   packet.data[1] = 0x34;
   packet.data[2] = 0x56;
   packet.data[3] = 0x78;
   packet.data[4] = 0x9A;
   packet.data[5] = 0xBC;
   packet.data[6] = 0xDE;
   packet.data[7] = 0xF0;
   packet.data[8] = 0x11;
   packet.data[9] = 0x22;

   // Transmit the data packet
   printf("1. Transmitting data packet:\n");
   transmit(packet);

   // Receive the data packet
   data_packet_t received_packet;
   bool is_valid = receive(&received_packet);
   if (is_valid)
   {
      printf("2. Received data packet:\n");
      printf("Packet ID: %d\n", received_packet.id);
      printf("Data Length: %d\n", received_packet.data_length);
      printf("Data: ");
      for (uint8_t i = 0; i < received_packet.data_length; i++)
      {
         printf("%02X ", received_packet.data[i]);
      }
      printf("\nCRC: %04X\n", received_packet.crc);
      printf("Packet received successfully.\n");
      printf("-----------------------------\n");
   }

   // Data packet corruption status
   if (!is_valid)
   {
      printf("2. Received data packet:\n");
      printf("Packet ID: %d\n", received_packet.id);
      printf("Data Length: %d\n", received_packet.data_length);
      printf("Data: ");
      printf("\nCRC: %04X\n", received_packet.crc);
      printf("Packet received successfully.\n");
      printf("-----------------------------\n");
      printf("3. Data packet corruption status: Data packet corrupted!\n");
      printf("-----------------------------\n");
   }
   else
   {
      printf("3. Data packet corruption status: Data packet valid.\n");
      printf("-----------------------------\n");
      printf("\n");
   }

   return 0;
}
