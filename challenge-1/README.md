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

```
# Challenge-1a
Solution by SHIVAM KUMAR (https://github.com/shivamskr151/Programming_Challenge/blob/main/challenge-1%20Data%20Packet%20Corruption%20Detection.c)

# Challenge-1b
* Write a function that takes data_packet as argument
* The function must count and return the number of data indexes filled with 1's.

Solution by [Manideep Pulluri](https://github.com/Manideep033/Challenges.git)
