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

    // Check the length of the input string
    size_t len = strlen(input_string);
    if (len != 10 || input_string[2] != '/' || input_string[5] != '/') {
        return INCORRECT;
    }

    // Extract day, month, and year from the input string
    int day = atoi(input_string);
    int month = atoi(input_string + 3);
    int year = atoi(input_string + 6);

    // Validate the day, month, and year values
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1 || year > 9999) {
        return INCORRECT;
    }

    // Assign values to the result_date structure
    result_date->date = (uint8_t)day;
    result_date->month = (uint8_t)month;
    result_date->year = (uint16_t)year;

    return SUCCESS;
}

int main() {
    char input[10];
    scanf("%s", input);
    my_date_t result;

    status_t status = string_to_date_converter(input, &result);

    if (status == SUCCESS) {
        printf("Conversion successful!\n");
        printf("Day: %d\n", result.date);
        printf("Month: %d\n", result.month);
        printf("Year: %d\n", result.year);
    } else if (status == NULL_PTR) {
        printf("NULL pointer error!\n");
    } else if (status == INCORRECT) {
        printf("Incorrect date format!\n");
    }

    return 0;
}
