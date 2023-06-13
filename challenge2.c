#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct my_date_t {
    uint8_t date;   // Day
    uint8_t month;  // Month
    uint16_t year;  // Year
} my_date_t;

typedef enum status_t {
    SUCCESS,    // Conversion successful
    NULL_PTR,   // NULL pointer passed as argument
    INCORRECT   // Incorrect values for date, month, or year
} status_t;

status_t string_to_date_converter(char* input_string, my_date_t* result_date) {
    if (!input_string || !result_date) {
        return NULL_PTR;
    }

    if (sscanf(input_string, "%2hhu/%2hhu/%4hu", &result_date->date, &result_date->month, &result_date->year) != 3) {
        return INCORRECT;
    }

    if (result_date->date < 1 || result_date->date > 31 || result_date->month < 1 || result_date->month > 12) {
        return INCORRECT;
    }

    return SUCCESS;
}

int main() {
    // Example usage
    char input_string[] = "13/06/2023";
    my_date_t result_date;

    status_t conversion_status = string_to_date_converter(input_string, &result_date);

    if (conversion_status == SUCCESS) {
        printf("Conversion successful:\n"
               "Date: %u\n"
               "Month: %u\n"
               "Year: %u\n",
               result_date.date, result_date.month, result_date.year);
    } else if (conversion_status == NULL_PTR) {
        printf("Error: NULL pointer passed as argument.\n");
    } else if (conversion_status == INCORRECT) {
        printf("Error: Incorrect values for date, month, or year.\n");
    }

    return 0;
}
