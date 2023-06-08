#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> 

typedef struct my_date_t {
    uint8_t date;
    uint8_t month;
    uint16_t year;
} my_date_t;

typedef enum status_t {
    SUCCESS,
    NULL_PTR,
    INCORRECT
} status_t;

status_t string_to_date_converter(char* input_string, my_date_t* result_date) {
    if (input_string == NULL || result_date == NULL) {
        return NULL_PTR;
    }

   
    int day, month, year;
    int status = sscanf(input_string, "%d/%d/%d", &day, &month, &year);
    if (status != 3) {
        return INCORRECT;
    }

    
    if (day < 1 || day > 31) {
        return INCORRECT;
    }

    if (month < 1 || month > 12) {
        return INCORRECT;
    }

    if (year < 1900 || year > 2100) {
        return INCORRECT;
    }

    
    result_date->date = (uint8_t)day;
    result_date->month = (uint8_t)month;
    result_date->year = (uint16_t)year;

    return SUCCESS;
}

int main() {
    char input_string[100];
    printf("Enter a date in the format DD/MM/YYYY: ");
    fgets(input_string, sizeof(input_string), stdin);

    my_date_t date;
    status_t status = string_to_date_converter(input_string, &date);
    if (status == SUCCESS) {
        printf("The date is %d/%d/%d\n", date.date, date.month, date.year);
    } else {
        printf("An error occurred while converting the date.\n");
    }

    return 0;
}
