// C program solution for the Data packet corruption Detection
#include <stdio.h>
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

uint16_t crc16_table[256];

void generate_crc16_table() {
    uint16_t polynomial = 0x1021;
    for (uint16_t i = 0; i < 256; i++) {
        uint16_t c = i << 8;
        for (size_t j = 0; j < 8; j++) {
            if (c & 0x8000) {
                c = (c << 1) ^ polynomial;
            } else {
                c <<= 1;
            }
        }
        crc16_table[i] = c;
    }
}

uint16_t calculate_crc(data_packet_t *packet) {
    uint16_t crc = 0xFFFF;
    crc = crc16_table[(crc >> 8 ^ packet->id) & 0xFF] ^ (crc << 8);
    crc = crc16_table[(crc >> 8 ^ packet->data_length) & 0xFF] ^ (crc << 8);
    for (int i = 0; i < packet->data_length; i++) {
        crc = crc16_table[(crc >> 8 ^ packet->data[i]) & 0xFF] ^ (crc << 8);
    }
    return ~crc;
}

int is_corrupted(data_packet_t *packet) {
    return packet->crc != calculate_crc(packet);
}

void print_packet(data_packet_t *packet) {
    printf("Packet ID: %d\n", packet->id);
    printf("Data length: %d\n", packet->data_length);
    printf("Data: ");
    for (int i = 0; i < packet->data_length; i++) {
        printf("%c", packet->data[i]);
    }
    printf("\n");
    printf("CRC: %04X\n", packet->crc);
}

int main() {
    generate_crc16_table();

    data_packet_t packets[] = {
        {1, 4, {'t', 'e', 's', 't'}, 0},
        {2, 5, {'h', 'e', 'l', 'l', 'o'}, 0}
        //{3, 6, {'w', 'o', 'r', 'l', 'd', '!'}, 0},
        //{4,7,{'p','a','c','k','e','t','s'},0}
    };
    int num_packets = sizeof(packets) / sizeof(packets[0]);

    for (int i = 0; i < num_packets; i++) {
        packets[i].crc = calculate_crc(&packets[i]);
        printf("Transmitted data packet %d:\n", i + 1);
        print_packet(&packets[i]);
        //printf("\n");
        printf("---------------------");
        printf("\n");
    }
    printf("\n");
    // corrupt the second packet
    packets[1].data[2] = 't';
    packets[1].data[3] = 'f';
    
    

    for (int i = 0; i < num_packets; i++) {
        printf("Received data packet %d:\n", i + 1);
        print_packet(&packets[i]);
        printf("Calculated CRC: %04X\n", calculate_crc(&packets[i]));
        printf("Packet is %s\n", is_corrupted(&packets[i]) ? "corrupted" : "not corrupted");
        printf("-----------------------------");
        //printf("\n");
        printf("\n");
    }

    return 0;
}
