# Data Packet Corruption Detection
* In a Wireless communciation device, multiple data packets are transferred over the air. 
* It is possible that data might get corrupted or lost before it reaches the destination.
* Create a method to identify if a data packet is corrupted
* Assume below format for the data packet

```
#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t{
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
}data_packet_t;

unit16_t calculate_crc(const data_packet_t* packet)
{
    * CRC calculation algorithm goes here
    * It should operate on the entire data packet except for the crc field
    * Return the calculated CRC
}

int is_packet_currupted(const data_packet_t* packet)
{
unit_t calculated_crc = calculate_crc(packet);
return (calculated_crc != packet->crc);
}


# FAQ's
* Links to Discussions
