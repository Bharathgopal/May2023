# Data Packet Corruption Detection
* In a Wireless communciation device, multiple data packets are transferred over the air. 
* It is possible that data might get corrupted or lost before it reaches the destination.
* Create a method to identify if a data packet is corrupted
* Assume below format for the data packet

```
#include <stdio.h>
#include <stdint.h>

typedef unsigned char           BYTE;
typedef unsigned short          WORD;


#define MAX_PACKET_DATA_LENGTH (50)
#define CRC_START               0xFFFF
#define CRC_POLY                0x1021


 


enum TrueorFalse{
False=0,
True
};


typedef struct data_packet_t{
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
}data_packet_t;


uint16_t crc_16( const unsigned char *input, unsigned int num_bytes) 
{ 
	uint8_t i; 	
	uint16_t crc; 
	crc = CRC_START; 
	while (num_bytes--) 
	{ 
		crc ^= *(unsigned char *)input++ << 8;
		for (i=0; i < 8; i++) 
		crc = crc & 0x8000 ? (crc << 1) ^ CRC_POLY : crc << 1;
 	} 
	return crc & CRC_START;
}

static BYTE ValidateCRC(data_packet_t pbyPktBuf) 
{ 	
	BYTE byStatus = True; 
	WORD wCRC = 0, wPktCRC = 0; 
	/* compute crc */ 
	wCRC = crc_16(&pbyPktBuf,pbyPktBuf.data_length);
	/* extract packet crc */ 
	wPktCRC = (pbyPktBuf.crc); 
	/* Now compare crc */ 
	if (wCRC != wPktCRC) 
	{ 
		printf("CRC Error , Expected CRC : %lu , Calculated CRC : %lu", wCRC, wPktCRC); 
		/*crc match failed */ 
		byStatus = False; 
	} 
	return byStatus; 
}

int main()
{
    /*Not Corrupted*/
	data_packet_t pkt;
 	pkt.id=12;
	pkt.data_length=3;
    pkt.data[0]=1;
	pkt.data[1]=2;
	pkt.data[2]=2;
    pkt.crc=crc_16(&pkt,pkt.data_length);

    int isCorrupted=ValidateCRC(pkt);
    
    if(!isCorrupted){
		printf("\nDATA Corrupted\n");
	}
	else
	{
		printf("\nDATA Correct\n");
	}
	
	/*corrupted case*/
	data_packet_t pkt1;
 	pkt1.id=12;
	pkt1.data_length=3;
    pkt1.data[0]=1;
	pkt1.data[1]=2;
	pkt1.data[2]=2;
    pkt1.crc=crc_16(&pkt1,pkt1.data_length);
    pkt1.data[0]=78;//introduce corruption
    isCorrupted=ValidateCRC(pkt1);

    if(!isCorrupted){
		printf("\nDATA Corrupted\n");
	}
	else
	{
		printf("\nDATA Correct\n");
	}
	return 0;
}	

```
# FAQ's
* Links to Discussions