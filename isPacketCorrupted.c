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

// Function to Calculate CRC

uint16_t calculateCRC(const uint8_t* data, uint8_t length) {
    uint16_t crc = 0xFFFF;  // Initial value for CRC

    while (length--) {
        crc ^= *data++;  // This step will perform XOR operation with next data byte

/*By performing bitwise AND operation with '0x0001' we can extract the LSB from the CRC Value

if the result is 1 the CRC value will be right shifted by 1 bit and then the XOR operation will take 

place with the polynomial 0xA001, if the LSB is 0 then the CRC value is simply right shifted by 1 bit. */

        for (int i = 0; i < 8; i++) {
            if (crc & 0x0001)  
                crc = (crc >> 1) ^ 0xA001;  
            else
                crc >>= 1;
        }
    }

    return crc;
}

// Function to check if a data packet is corrupted or not


bool isPacketCorrupted(data_packet_t packet) {
    uint16_t calculatedCRC = calculateCRC(packet.data, packet.data_length);

    if (calculatedCRC == packet.crc)
        return 0;  // Not corrupted
    else
        return 1;  // Corrupted
}

int main() {
    
    data_packet_t packet;
    packet.id = 1;
    packet.data_length = 5;
    packet.data[0] = 0x12;   //Hexa Decimal Number equal to 18 in Decimal
    packet.data[1] = 0x34;
    packet.data[2] = 0x56;
    packet.data[3] = 0x78;
    packet.data[4] = 0x90;
    packet.crc = calculateCRC(packet.data, packet.data_length);
    
    packet.data[2] = 0xAA;     /* if we comment this line we will get the output as Packet is not Corrupted
		             if we want to check whether the code is working when we change the data or the data is changed, we 
                                                   can remove the comment and the output says the Packet is Corrupted */


    if (isPacketCorrupted(packet))
        printf("Packet is corrupted.\n");
    else
        printf("Packet is not corrupted.\n");
    return 0;
}
