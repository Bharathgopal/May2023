#include "packetiser.h"

status_t packetiser(packet_t* result_packet, headers_t* result_headers, uint8_t* input_data, uint8_t input_data_length)
{
    status_t function_status = SUCCESS;

    if (NULL == result_packet || NULL == result_headers || NULL == input_data)
    {
#if DEBUG_PRINT
        printf("Null pointer inputs\n");
#endif
        function_status = NULL_PTR;
    }
    else
    {
        if (NULL == memcpy((uint8_t *)&result_packet->headers, (uint8_t *)&result_headers, HEADER_LENGTH))
        {

#if DEBUG_PRINT
            printf("Copy failure\n");
#endif

            function_status = NULL_PTR;
        }
        
        if (NULL != memcpy((uint8_t *)&result_packet->data[0], input_data, input_data_length))
        {

#if DEBUG_PRINT
            printf("Copy failure\n");
#endif
            function_status = NULL_PTR;
        }
        result_packet->crc = crc_16((uint8_t *)&result_packet->data[0], MAX_DATA_LENGTH);
#if DEBUG_PRINT
            printf("CRC = %X\n",result_packet->crc);
#endif
    }
    return function_status;
}

void display_packet(packet_t* input_packet)
{
#if DEBUG_PRINT
    printf("Headers: %X, %ld\n", input_packet->headers.type, input_packet->timestamp);
    printf("Data = \n");

    for(int index= 0; index<= MAX_DATA_LENGTH; index++)
    {
        printf("%02X \t, ", input_packet->data[index]);
    }
    printf("CRC = %0X \n", input_packet->crc);
#endif
}

status_t verify_crc(packet_t* input_packet)
{
    uint16_t calculated_crc = crc_16((uint8_t*)&input_packet->data[0], MAX_DATA_LENGTH);

#if DEBUG_PRINT
    printf("Calculated CRC = %X, Sent CRC= %X\n", input_packet->crc, calculated_crc);
#endif

    if(input_packet->crc == calculated_crc)
    {
        return SUCCESS;
    }
    return ERROR;
}