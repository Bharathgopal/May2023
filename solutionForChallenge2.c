#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct my_date_t
{
    uint8_t date;    /* date */
    uint8_t month;   /* month */
    uint16_t year;   /* year */
} my_date_t;

typedef enum status_t
{
    SUCCESS,    /* Function has successfully converted the string to structure */
    NULL_PTR,   /* Function is given NULL pointers to work with */
    INCORRECT   /* Incorrect values for date or month or year */
} status_t;


//Function to convert the string formated date to a structure


status_t string_to_date_converter(char* input_string, my_date_t* result_date)
{
    if (input_string == NULL || result_date == NULL) {           //To check whether the input string is null if it is null then return null_ptr
        return NULL_PTR;
    }

    // To Check if the input string has the correct format as DD/MM/YYYY

    if (strlen(input_string) != 10){
        if(input_string[2] != '/'){
            if(input_string[5] != '/'){
                  return INCORRECT;
            }
        }
    }
        
      

    char date_str[3], month_str[3], year_str[5];        /*Here we are creating a new char array variables named as date_str[3], month_str[3], year_str[5] and extracting the input from the input_string
                                                                                       and also by using string copy function we are assigning input to the variables by specifying the size */
    strncpy(date_str, input_string, 2);
    date_str[2] = '\0';                                                    //we are assigning the 3 character to '/' to match the input format
    strncpy(month_str, input_string + 3, 2);
    month_str[2] = '\0';
    strncpy(year_str, input_string + 6, 4);
    year_str[4] = '\0';

  
/*Here we are converting the extracted strings to integers by using atoi function*/

    int date = atoi(date_str);                      
    int month = atoi(month_str);
    int year = atoi(year_str);
    
/*Here we are assigning the converted values of string to the result_date structure*/

    result_date->date = (uint8_t)date;                   
    result_date->month = (uint8_t)month;
    result_date->year = (uint16_t)year;
    

    // Now we should check that the date, month and year are valid or not


    if (date < 1 || date > 31){
        if(month < 1 || month > 12){
            if(year < 0){
                return INCORRECT;
            }
        }
    } 
   
    return SUCCESS;
}

int main()
{
    char input_string[] = "10/04/2002";         //input_string
    my_date_t result_date;

    status_t conversion_status = string_to_date_converter(input_string, &result_date);

    if (conversion_status == SUCCESS) {
        printf("Function has successfully converted the string to structure\n");
        printf("Date: %d\n", result_date.date);
        printf("Month: %d\n", result_date.month);
        printf("Year: %d\n", result_date.year);
    }
    else if (conversion_status == NULL_PTR) {
        printf("Function is given NULL pointers to work with\n");
    }
    else if (conversion_status == INCORRECT) {
        printf("Incorrect values for date or month or year\n");
    }

    return 0;
}