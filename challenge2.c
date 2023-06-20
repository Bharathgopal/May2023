/** # Date String to Structure conversion
* In a application, the date is stored as a string and for computations, converting the string to number is required.
* Write a function to convert the string formated date to a structure as per the below code
* Return appropriate error values if the conversion is not successful

## Inptu string format
```
    DD/MM/YYYY
```

## Output Structure format
```
typedef struct my_date_t
{
    uint8_t date;       /*<<< date */
    uint8_t month;      /*<<< month */
    uint16_t year;      /*<<< year   */
}my_date_t; 
```
**/
#include <stdio.h>
#include <stdint.h>

typedef struct my_date_t
{
    uint8_t date;       
    uint8_t month;      
    uint16_t year;      
} my_date_t;

typedef enum status_t
{
    SUCCESS,    
    NULL_PTR,   
    INCORRECT   
} status_t;

status_t string_to_date_converter(char* input_string, my_date_t* result_date)
{
    if (input_string == NULL || result_date == NULL)
    {
        return NULL_PTR;
    }
  
    int day, month, year;
    if (sscanf(input_string, "%d/%d/%d", &day, &month, &year) != 3)
    {
        return INCORRECT;
    }
  
    
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0)
    {
        return INCORRECT;
    }
  
    result_date->date = (uint8_t)day;
    result_date->month = (uint8_t)month;
    result_date->year = (uint16_t)year;
  
    return SUCCESS;
}

int main()
{
    
    char input_string[20];
    scanf("%s", input_string);
    my_date_t result_date;
    status_t status = string_to_date_converter(input_string, &result_date);
  
    if (status == SUCCESS)
    {
        printf("Date: %d\n", result_date.date);
        printf("Month: %d\n", result_date.month);
        printf("Year: %d\n", result_date.year);
    }
    else if (status == NULL_PTR)
    {
        printf("Error: NULL pointers\n");
    }
    else if (status == INCORRECT)
    {
        printf("Error: Incorrect date format\n");
    }
  
   return 0;
}