#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct my_date_t
{
    uint8_t date;       
    uint8_t month;      
    uint16_t year;      
}my_date_t;

typedef enum status_t
{
    SUCCESS,                    
    NULL_PTR,                   
    INCORRECT                   
}status_t;

status_t string_to_date_converter(char* input_string, my_date_t* result_date)
{
    
    if(input_string==NULL || result_date==NULL)
    {
        return NULL_PTR;
    }
    int date,month,year;
    
    sscanf(input_string,"%d/%d/%d",&date,&month,&year);
    
    
    if(date==0 || month==0 || year==0)
    {
        return INCORRECT;
    }
    
    
    if(date>=1 || date<=31 || month>=1 || month<=12 || year!=0)
    {
        
        if((month==2 && (year%4==0))&& date>29)
        {
            return INCORRECT;
        }
        
        else if((month==2 && (year%4!=0))&& date>28)
        {
            return INCORRECT;
        }
       
        else if(month==4 || month==6 || month==9 || month==11)
        {
            if(date==31)
            {
                return INCORRECT;
            }
        }
    }
    
    result_date->date=(uint8_t)date;
    result_date->month=(uint8_t)month;
    result_date->year=(uint16_t)year;
    return SUCCESS;
}


int main()
{
    char str_date[]="3/2000";
    my_date_t given_date;
    
    status_t status = string_to_date_converter(str_date,&given_date);
    
    if(status==SUCCESS)
    {
        printf("CONVERTED SUCCESSFULLY\n");
        printf("DATE= %d\n",given_date.date);
        printf("MONTH= %d\n",given_date.month);
        printf("DATE= %d\n",given_date.year);
    }
    
    else if(status==NULL_PTR)
    {
        printf("ENTER DATE IN PROPER FORMAT");
    }
                                
    else if(status==INCORRECT)
    {
        printf("ENTER PROPER DATE");
    }
    
    return 0;
}