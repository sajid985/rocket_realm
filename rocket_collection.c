#include "rocket.h"
#include <string.h>
#include <stdio.h>

//initializes an empty rocketsys collection, setting the size to 0
int rocketsys_collection_init(RocketCollection *rockets) {
	rockets-> size = 0;
	return ERR_SUCCESS;
}

//appending a copy of the rocketsystem to the end of the collection if there's space in the collection
int rocketsys_append(RocketCollection *rockets, const Rocket *rocketsystem) {
	if (rockets -> size >= MAX_ARR) {
		return ERR_MAX_CAPACITY;
	}
	
	Rocket *temp_rocketsys = &(rockets -> rockets[rockets->size]); 
	rockets -> size++;
	
	strcpy(temp_rocketsys->name, rocketsystem -> name);
	temp_rocketsys->status = rocketsystem -> status;
	temp_rocketsys->data = rocketsystem -> data;
	
	return ERR_SUCCESS;
}

//loops thru the whole collection to see if the names equal. if not found, return ERR_SYS_NOT_FOUND
int rocketsys_find(const RocketCollection *rockets, const char *name) {
	for (int i=0; i < (rockets -> size); i++) {	
		if (strcmp(rockets->rockets[i].name, name) == 0) {
			return i;
		}
	}
	return ERR_SYS_NOT_FOUND;
}

//returning an error if there's no rockets stored in the collection
//prints all the rockets in order of index
int rocketsys_collection_print(RocketCollection *rockets) {
	if (rockets -> size == 0) {
		return ERR_NO_DATA;
	}
	
	for (int i=0; i < (rockets -> size); i++) {
		rocketsys_print(&(rockets -> rockets[i]));
	}
	
	return ERR_SUCCESS;
}


//checks to see if it's valid index, if it's valid, remove it from the collection and shift everything over to the left.
int rocketsys_remove(RocketCollection *rockets, int index) {
	//check if it's a valid index with the size of the array
	if ((index < 0) || (index > (rockets->size - 1))) {
		return ERR_INVALID_INDEX;
	}
	
	if ((rockets -> size) == 0) {
		return ERR_NO_DATA;
	}
	
	//overwrite the rocketsystem at index i. keep overwriting by making subcol[i] = subcol[i+1] all the way to n - 1
	for (int j = 0; j < (rockets->size - index); j++) {
			rockets->rockets[index + j] = rockets->rockets[index + j + 1];
	}
	
	//substract subcol size by 1
	rockets->size = rockets->size - 1;
	return ERR_SUCCESS;
}

//creating a function which lets users filter a specific status they are looking for by letting them input (1,0,*). It checks for correct size, does bit operations to create the masks and it checks for valid input at the same time. Then we check if we can append it to the new collection.
int rocketsys_filter(const RocketCollection *src, RocketCollection *dest, const unsigned char *filter) {

	//I need to make sure the size being inputted is 8 exactly using strlen
	if (strlen(filter) != 8) {
		return ERR_INVALID_STATUS;
	}
	
	char f_mask = 0;
	char w_mask = 0;
	char bit_pos;
	
	//make sure in the string, each item is either 1, 0, or *. I can check with if statements
	for (int i=0; i<8; i++) {
		if (filter[i] == '1') {	
			//place bit 1 in bit position 7
			bit_pos = (1 << (7-i));
			f_mask = f_mask | bit_pos;
		} else if (filter[i] == '*') {
			bit_pos = (1 << (7-i));
			w_mask = w_mask | bit_pos;
		} else if (filter[i] == '0') {
			continue;
		} else {
			return ERR_INVALID_STATUS;
		}
	}
	
	f_mask = ~f_mask;
	
	//now we loop through the src collection and if the equation given == all the bits being 1 or if it equals to 255. then we can add append it to *dest.
	
	for (int i=0; i<(src->size); i++) {
		unsigned char computed = ((f_mask ^ (src -> rockets[i]).status) | w_mask);
		if (computed == 255) {
			rocketsys_append(dest, &(src -> rockets[i]));
		}
	}
	
	return ERR_SUCCESS;
}
