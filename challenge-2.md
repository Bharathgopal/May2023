# Date String to Structure conversion
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

### Conversion status 
```
typedef enum status_t
{
    SUCCESS,                    /**< Function has successfully converted the string to structure */
    NULL_PTR,                   /**< Function is given NULL pointers to work with */
    INCORRECT                   /**< Incorrect values for date or month or year */
}status_t;

```

### Function prototype
```
/**
 * @brief Function to convert string of the format DD/MM/YYYY to my_date_t structure
 * 
 * @param input_string String which needs to be converted
 * @param result_time Resultant structure to hold the converted string
 * @return status_t SUCCESS if conversion is done, status_t code otherwise.
 */
status_t string_to_date_converter(char* input_string, my_date_t* result_date);
```

#include<stdio.h>
#include<stdint.h>
typedef struct my_date_t
{
    uint8_t date;       /*<<< date */
    uint8_t month;      /*<<< month */
    uint16_t year;      /*<<< year   */
}my_date_t;

typedef enum status_t
{
    SUCCESS,                    /**< Function has successfully converted the string to structure */
    NULL_PTR,                   /**< Function is given NULL pointers to work with */
    INCORRECT                   /**< Incorrect values for date or month or year */
}status_t;

status_t string_to_date_converter(char* input_string, my_date_t* result_date){
if(input_string==NULL){
    return NULL_PTR;
}

int year,month,day;
int status=sscanf(input_string,"%d/%d/%d",&day,&month,&year);
if(status!=3){
    return INCORRECT;
}

if(day<0 || day>31 || month<0 || month>12 || year<0){
    return INCORRECT;
} 
result_date->date=(uint8_t)day;
result_date->month=(uint8_t)month;
result_date->year=(uint16_t)year;


return SUCCESS;

}


int main(){

char cDate[20];
scanf("%s",cDate);
my_date_t sDate;
status_t eStatus;
eStatus=string_to_date_converter(cDate,&sDate);

if (eStatus == SUCCESS)
{
    printf("Date: %d\n", sDate.date);
    printf("Month: %d\n", sDate.month);
    printf("Year: %d\n", sDate.year);
}
else if (eStatus == NULL_PTR)
{
    printf("Error: NULL pointer\n");
}
else if (eStatus == INCORRECT)
{
    printf("Error: Incorrect date format\n");
}


return 0;
}
