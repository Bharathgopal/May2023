#include <stdio.h>
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH 5

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

uint16_t crcValue(const uint8_t* data, uint8_t length) {
    uint16_t crc = 0;
    for (int i = 0; i < length; i++) {
        crc ^= data[i];  
        /* here we are xoring the every data[i] values then the 
        final crc xored values are returned*/
    }
    return crc;
}

int crcChecking(const data_packet_t* packet) {
    uint16_t crc = crcValue(packet->data, packet->data_length);  

    // Compare the received data packet CRC with the original data packet CRC
    if (crc != packet->crc) {
        printf("Packet is corrupted\n");
        return 1;  // Packet is corrupted
    } else {
        printf("Packet is not corrupted\n");
        return 0;   // Packet is not corrupted
    }
}


int main(){
    data_packet_t packet1;
    packet1.id = 1;
    packet1.data_length = 5;
    packet1.data[0] = 1;
    packet1.data[1] = 2;
    packet1.data[2] = 3;
    packet1.data[3] = 4;
    packet1.data[4] = 5;
    // here we are taking the crc value of the entire original data packet before transmission
    packet1.crc = crcValue(packet1.data,packet1.data_length); 

    // let say now we have transmitted this packet
    /* now in receiver we have to check the crc value of the received packet 
    with the crc value of the original data packet  */
    crcChecking(&packet1); //---->Packet is not corrupted

    // let say now some of the data in the packet1 is changed (i.e.  data is corrupted)
    packet1.data[4] = 6;  // here the data[4] was previously 5 & now is 6
    crcChecking(&packet1); // ----> //---->Packet is corrupted 
    // because the crc value of the original data packet is different with the recieved packet crc value 
    
    return 0;
}

