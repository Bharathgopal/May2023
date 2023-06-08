#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

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
    if (input_string == NULL || result_date == NULL)
        return NULL_PTR;

    char* endptr;
    uint8_t day = strtol(input_string, &endptr, 10);
    if (*endptr != '/' || day == 0)
        return INCORRECT;

    uint8_t month = strtol(endptr + 1, &endptr, 10);
    if (*endptr != '/' || month == 0)
        return INCORRECT;

    uint16_t year = strtol(endptr + 1, &endptr, 10);
    if (*endptr != '\0' || year == 0)
        return INCORRECT;

    result_date->date = day;
    result_date->month = month;
    result_date->year = year;

    return SUCCESS;
}

int main() {
    char input_string[] = "31/12/2023";
    my_date_t result_date;

    status_t status = string_to_date_converter(input_string, &result_date);
    if (status == SUCCESS) {
        printf("Date: %02d/%02d/%04d\n", result_date.date, result_date.month, result_date.year);
    } else if (status == NULL_PTR) {
        printf("Error: NULL pointers provided.\n");
    } else if (status == INCORRECT) {
        printf("Error: Incorrect date format or values.\n");
    }

    return 0;
}
