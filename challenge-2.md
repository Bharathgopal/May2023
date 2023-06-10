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
