#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct my_date_t
{
    uint8_t date;
    uint8_t month;
    uint16_t year;
} my_date_t;

int parseDateString(const char* dateString, my_date_t* result) {
    if (dateString == NULL || result == NULL || strlen(dateString) != 10)
        return -1;

    char dayStr[3], monthStr[3], yearStr[5];
    sscanf(dateString, "%2[^/]/%2[^/]/%4s", dayStr, monthStr, yearStr);
    

    int day = atoi(dayStr);
    int month = atoi(monthStr);
    int year = atoi(yearStr);

    result->date = (uint8_t)day;
    result->month = (uint8_t)month;
    result->year = (uint16_t)year;
    
    return 0;
}

int main() {
     char dateString[12];
    fgets(dateString, sizeof(dateString), stdin);
    my_date_t result;
    
    if (0==parseDateString(dateString, &result)) {
        printf("Date: %02u/%02u/%04u\n", result.date, result.month, result.year);
    } else {
        printf("Failed to parse date string.\n");
    }
    
    return 0;
}
