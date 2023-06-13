#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct my_date_t {
    uint8_t date;
    uint8_t month;
    uint16_t year;
} my_date_t;

typedef enum status_t {
    SUCCESS,        /* Function has successfully converted the string to structure */
    NULL_PTR,       /* Function is given NULL pointers to work with */
    INCORRECT       /* Incorrect values for date or month or year */
} status_t;

status_t string_to_date_converter(char* input_string, my_date_t* result_date) {
    if (input_string == NULL || result_date == NULL) {
        return NULL_PTR;
    }

    int day, month, year;
    if (sscanf(input_string, "%d/%d/%d", &day, &month, &year) != 3) {
        return INCORRECT;
    }

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) {
        return INCORRECT;
    }

    result_date->date = (uint8_t)day;
    result_date->month = (uint8_t)month;
    result_date->year = (uint16_t)year;

    return SUCCESS;
}

int main() {
    char input_string[] = "10/06/2023";
    my_date_t result_date;

    status_t status = string_to_date_converter(input_string, &result_date);
    if (status == SUCCESS) {
        printf("Date: %d/%d/%d\n", result_date.date, result_date.month, result_date.year);
    } else {
        printf("Conversion failed with status: %d\n", status);
    }
    return 0;
}