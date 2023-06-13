#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
typedef struct my_date_t{
	uint8_t date;  /*< date */
	uint8_t month; /*< month */
	uint16_t year; /*< year */
}my_date_t;
typedef enum status_t{
	SUCCESS,    /*< Function has successfully converted the string to structure */
    NULL_PTR,   /*< Function is given NULL pointers to work with */
    INCORRECT   /*< Incorrect values for date or month or year */
}status_t;
status_t string_to_date_converter(char* input_string,my_date_t* dateStruct){
	if(input_string==NULL||dateStruct==NULL){
		return NULL_PTR;
	}

	int dd,mm,yyyy;
	if(sscanf(input_string,"%d/%d/%d",&dd,&mm,&yyyy)!=3){
		return INCORRECT;
	}
	if(dd<1||dd>31||mm<1||mm>12||yyyy<0){
		return INCORRECT;
	}

	dateStruct->date = (uint8_t)dd;
    dateStruct->month = (uint8_t)mm;
    dateStruct->year = (uint16_t)yyyy;
	return SUCCESS;
}
int main(){
	my_date_t date;
	char str[12];
	printf("Enter the date in format(DD/MM/YYYY):");
	scanf("%s",str);
	status_t result=string_to_date_converter(str,&date);
	if(result==SUCCESS){
	printf("Function has successfully converted the string to structure");
	}else if(result==NULL_PTR){
	printf("Function is given NULL pointers to work with");
	}else if(result==INCORRECT){
	printf("Incorrect values for date or month or year");
	}
	return 0;
}