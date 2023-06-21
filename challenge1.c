#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
uint8_t id;
uint8_t data_length;
uint8_t data[MAX_PACKET_DATA_LENGTH];
uint16_t crc;
} data_packet_t;
static const uint16_t crc_table[256] = {
};
uint16_t calculate_crc(const uint8_t* data, uint8_t length) {
uint16_t crc = 0xFFFF;

while (length--) {
    crc = (crc >> 8) ^ crc_table[(crc ^ *data++) & 0xFF];
}
return crc;
}
int is_packet_corrupted(const data_packet_t* packet) {
uint16_t calculated_crc = calculate_crc(packet->data, packet->data_length);
return (calculated_crc != packet->crc);
}