#include "rocket.h"
#include <string.h>
#include <stdlib.h>

//initializing the rocket, it will return ERR_SUCCESS;. String literals like the one that would be passed in automatically already have null-terminators
int rocketsys_init(Rocket *rocket, const char *name, char status) {
	strncpy(rocket->name, name, 16);
	rocket->name[16] = '\0';
	
	rocket->status = status;
	rocket->data = 0;
	
	return ERR_SUCCESS;
}

//printing the rockets info in a consistent format.
int rocketsys_print(Rocket *rocket) {
	
	printf("%-16s: ", rocket->name);
	
	rocketsys_status_print(rocket);
	
	unsigned int data_value;
	if (rocketsys_data_get(rocket, &data_value) == ERR_SUCCESS) {
		printf(" Data: %08X", data_value);
	}
	
	printf("\n"); 		
	
	return ERR_SUCCESS;

}


//We're setting the status for a certain status, from the 5 specified. We look for which status we're changing and do bit operatios to set the value without affecting the other bits.
int rocketsys_status_set(Rocket *rocket, unsigned char status, unsigned char value) {

	if (value > 3 || value < 0) {return ERR_INVALID_STATUS;}
	
	if (status == 1 || status == 3 || status > 7 || status < 0) {
		return ERR_INVALID_STATUS;

	} else if (status == STATUS_RESOURCE) {
		// clear the bit first at the spot then set it
		char bit_pos = 3;
		(rocket -> status) = (rocket -> status) & ~bit_pos;
		
		//then set it
		(rocket -> status) = (rocket -> status) | value;
		return ERR_SUCCESS;
		
	} else if (status == STATUS_PERFORMANCE) {
		
		char bit_pos = 12;
		(rocket -> status) = (rocket -> status) & ~bit_pos;
		(rocket -> status) = (rocket -> status) | (value << 2);
		return ERR_SUCCESS;
		
	} else if (status == STATUS_ERROR) {
		
		if ((value != 0) && (value != 1)) {return ERR_INVALID_STATUS;} 
		char bit_pos = 16;
		(rocket -> status) = (rocket -> status) & ~bit_pos;
		(rocket -> status) = (rocket -> status) | (value << 4);
		
		return ERR_SUCCESS;
		
	} else if (status == STATUS_ACTIVITY) {
		
		if ((value != 0) && (value != 1)) {return ERR_INVALID_STATUS;} 
		char bit_pos = 32;
		(rocket -> status) = (rocket -> status) & ~bit_pos;
		(rocket -> status) = (rocket -> status) | (value << 5);
		
		return ERR_SUCCESS;
		
	} else if (status == STATUS_DATA) {
		
		if ((value != 0) && (value != 1)) {return ERR_INVALID_STATUS;}
		char bit_pos = 64;
		(rocket -> status) = (rocket -> status) & ~bit_pos;
		(rocket -> status) = (rocket -> status) | (value << 6);
		
		return ERR_SUCCESS;

	} else if (status == STATUS_POWER) {
		
		if ((value != 0) && (value != 1)) {return ERR_INVALID_STATUS;} 
		char bit_pos = 128;
		(rocket -> status) = (rocket -> status) & ~bit_pos;
		(rocket -> status) = (rocket -> status) | (value << 7);
		
		return ERR_SUCCESS;	
	} 
	
}

//if there's data present, save it to dest and reset the data queued in the status. If there's no data, return error and set dest to 0.
int rocketsys_data_get(Rocket *rocket, unsigned int *dest) {
	
	//checking if there's no data in data queued, if none, set *dest to 0 and send error
	if ((int)(((rocket -> status) & (1 << 6)) >> 6) == 0) {
		*dest = 0;
		
		return ERR_NO_DATA;
	} else {
	
		//if yes data, take the data, and set dest to that data. Set data field to 0 and make data queued bit 0.
		*dest = (rocket->data);
		
		rocket->data = 0;
		rocketsys_status_set(rocket, STATUS_DATA, 0);
		
		return ERR_SUCCESS;
	}
	
	
}

//Printing out the status for the rocket seperated by |.
int rocketsys_status_print(const Rocket *rocket) {
	int status_bit;
	
	//PWR
	status_bit = ((rocket -> status) & (1 << 7)) >> 7;
	printf("(PWR: %d|", status_bit);
	
	//DATA
	status_bit = ((rocket -> status) & (1 << 6)) >> 6;
	printf("DATA: %d|", status_bit);
	
	//ACT
	status_bit = ((rocket -> status) & (1 << 5)) >> 5;
	printf("ACT: %d|", status_bit);
	
	//ERR
	status_bit = ((rocket -> status) & (1 << 4)) >> 4;
	printf("ERR: %d|", status_bit);
	
	//PERF
	status_bit = 2*(((rocket -> status) & (1 << 3)) >> 3) + (((rocket -> status) & (1 << 2)) >> 2);
	printf("PERF: %d|", status_bit);
	
	//RES
	
	status_bit = 2*(((rocket -> status) & (1 << 1)) >> 1) + (((rocket -> status) & (1 << 0)) >> 0);
	printf("RES: %d)", status_bit);
	
	return ERR_SUCCESS;
}


//New data is set for a rocket while saving previos data if old_data isn't null. Data queued is switched on.
int rocketsys_data_set(Rocket *rocket, unsigned int new_data, unsigned int *old_data) {
	if (old_data != NULL) {
		*old_data = (rocket -> data);	
	} 
	
	rocket -> data = new_data;
	rocketsys_status_set(rocket, STATUS_DATA, 1);

	return ERR_SUCCESS;
}


void rocketsys_status_conv(char *str) {
	char converted[MAX_STR] = ""; 

	for(int i=0; i<6; i++) {
		if (str[i] == '0') {
			if (i > 3) {
				strcat(converted,"00");
			} else {
				strcat(converted,"0");
			}
	
		} else if (str[i] == '1'){
			if (i > 3) {
				strcat(converted,"01");
			} else {
				strcat(converted,"1");
			}

		} else if (str[i] == '2' && i > 3) {
			strcat(converted,"10");
		} else if (str[i] == '3' && i > 3) {
			strcat(converted,"11");
		} else {
			if (i > 3) {
				strcat(converted,"**");
			} else {
				strcat(converted,"*");
			}
		}

	}
	strcat(converted,"\0");
	
	strcpy(str, converted);
}








































