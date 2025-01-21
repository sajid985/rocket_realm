#include <stdio.h>
#include <stdlib.h>
#include "rocket.h"

#define MENU_ADD 1
#define MENU_PRINT 2
#define MENU_PRINTALL 3
#define MENU_STATUS 4
#define MENU_REMOVE 5
#define MENU_FILTER 6
#define MENU_DATA 7
#define MENU_EXIT 0
#define MENU_MIN 0
#define MENU_MAX 7

int print_menu(int *choice);
int print_definitions();

int main() {
    
    int user_inp;
    int return_value;
    char name[MAX_STR];    
    
    RocketCollection full_coll;  
    rocketsys_collection_init(&full_coll);
    
    RocketCollection dest_coll;  
    rocketsys_collection_init(&dest_coll);  

    while(1) {
		char status = 0;
        return_value = print_menu(&user_inp);
		//determine the input using io
        if (user_inp == MENU_ADD) {
            
            printf("Name the rocket (max 16 chars, no spaces): ");
            scanf("%s", name); 

            Rocket rocket;
            rocketsys_init(&rocket, name, status);
			
			printf("Rocket '%s' added successfully.\n", name);
			
            return_value = rocketsys_append(&full_coll, &rocket);
            if (return_value == ERR_MAX_CAPACITY) {
                printf("Sorry, the RocketCollection if full.");
            }
        } else if (user_inp == MENU_PRINT) {

			printf("Enter name of rocket to print: ");
            scanf("%s", name);
            
            int index_find = rocketsys_find(&full_coll, name);
            
            if (index_find == ERR_SYS_NOT_FOUND) {
            	printf("Sorry, I can't find any rocket with that name! \n");
            } else {
            	rocketsys_print(&(full_coll.rockets[index_find]));
            }
           

        } else if (user_inp == MENU_PRINTALL) {
        	rocketsys_collection_print(&full_coll);

        } else if (user_inp == MENU_STATUS) {
        	
       		char statusV;
        	char newV;
        	
            print_definitions();
        	printf("Enter: <Rocket Name> <Status ID, 7, 6, 5, 4, 2, 0> <New Value (0-3)>: ");
            scanf("%s %hhd %hhd", name, &statusV, &newV);
            
            if (newV > 3 || newV < 0) {
				printf("Invalid value, make sure it's between 0 - 3 (inclusive).\n");
				continue;
			} else if (status == 1 || status == 3 || status > 7 || status < 0) {
				printf("Invalid status, make sure it's one of the values listed.\n");
				continue;
			}
            
            int index_find = rocketsys_find(&full_coll, name);
            
            if (index_find == ERR_SYS_NOT_FOUND) {
            	printf("Sorry, I can't find any rocket with that name! \n");
            } else {
            	return_value = rocketsys_status_set(&(full_coll.rockets[index_find]), statusV, newV); 
            	
            	if (return_value == ERR_INVALID_STATUS) {
            		printf("Invalid status provided\n");
            		continue;
            	}
            	printf("Status updated successfully.\n");
            }
            
           
        	
        } else if (user_inp == MENU_REMOVE) {
            
            char index;
            printf("Enter an index to remove from the collection (0 to collection size - 1): ");
            scanf("%hhd", &index);
            
            return_value = rocketsys_remove(&full_coll, (int)(index));
            
            if (return_value == ERR_INVALID_INDEX) {
            	printf("You provided an invalid index!\n");
            } else {
            	printf("Rocket removed successfully.\n");
            }

        } else if (user_inp == MENU_FILTER) {
            // get an input of 6 numbers as chars, and create a filtered list for it.
            rocketsys_collection_init(&dest_coll);
            char six_chars[MAX_STR];

            print_definitions();

            //I will consider inputs that aren't 1 or 0 as * to avoid errors
            printf("You can input a valid power level or '*' indicating not specificed in the filtering\n");
            printf("%-15s (*, 0, 1):\n", "Power");
            scanf("%c", &six_chars[0]);
            while (getchar() != '\n');
            printf("%-15s (*, 0, 1):\n", "Data");
            scanf("%c", &six_chars[1]);
            while (getchar() != '\n');
            printf("%-15s (*, 0, 1):\n", "Activity");
            scanf("%c", &six_chars[2]);
            while (getchar() != '\n');
            printf("%-15s (*, 0, 1):\n", "Error");
            scanf("%c", &six_chars[3]);
            while (getchar() != '\n');
            printf("%-15s (*, 0, 1, 2, 3):\n", "Performance");
            scanf("%c", &six_chars[4]);
            while (getchar() != '\n');
            printf("%-15s (*, 0, 1, 2, 3):\n", "Resource");
            scanf("%c", &six_chars[5]);
            while (getchar() != '\n');
           
            six_chars[6] = '\0';

            rocketsys_status_conv(six_chars);
            
            return_value = rocketsys_filter(&full_coll, &dest_coll, six_chars);
            
            if (return_value == ERR_INVALID_STATUS) {
            	printf("You provided an invalid status!\n");
            } else {
            	printf("Filtered status appended successfully.\n");
            }

            printf("\nFiltered List:\n");
            rocketsys_collection_print(&dest_coll);

        } else if (user_inp == MENU_DATA) {
            
            unsigned int hexValue;
            unsigned int oldValue;
            
            printf("Enter: <Rocket Name> <New Data in Hex>: ");
            scanf("%s %X", name, &hexValue);
            
            int index_find = rocketsys_find(&full_coll, name);
            
            if (index_find == ERR_SYS_NOT_FOUND) {
            	printf("Sorry, I can't find any rocket with that name! \n");
            } else {
            	
            	//Now we found the index, we check if there is data waiting to be printed
            	int outValue = rocketsys_data_get(&(full_coll.rockets[index_find]), &oldValue);
            	if (outValue == ERR_SUCCESS) {
            		printf("%d\n", oldValue);
            	}
            	
            	//Overwrite the data by using the set data function.
            	rocketsys_data_set(&(full_coll.rockets[index_find]), hexValue, &oldValue);
            
            	printf("Data updated successfully.\n");
            }

        } else if (user_inp == MENU_EXIT) {
            //Exit the program
            printf("Program Exiting...");
            return MENU_EXIT;

        } else {
            printf("Invalid option, choose one of the numbers on the menu!\n");
        }
    }
    return MENU_EXIT;
}


int print_menu(int *choice) {
    if (choice == NULL) {
        return ERR_NULL_POINTER;
    }

    *choice = 0;

    do {
        printf("\n--- Rocket Management Menu ---\n");
        printf("%d. Add Rocket\n", MENU_ADD);
        printf("%d. Print Rocket\n", MENU_PRINT);
        printf("%d. Print All rockets\n", MENU_PRINTALL);
        printf("%d. Set Rocket Status\n", MENU_STATUS);
        printf("%d. Remove Rocket\n", MENU_REMOVE);
        printf("%d. Filter rockets\n", MENU_FILTER);
        printf("%d. Set Rocket Data\n", MENU_DATA);
        printf("%d. Exit\n", MENU_EXIT);
        printf("Select an option: ");
        scanf("%d", choice);
        while (getchar() != '\n');

        if (*choice < MENU_MIN || *choice > MENU_MAX) {
            printf("Error: Invalid choice. Please try again.\n");
        }
    } while (*choice < MENU_MIN || *choice > MENU_MAX);

    return ERR_SUCCESS;
}

int print_definitions() {

    printf("\n<------------------STATUS ID DEFINITIONS------------------>\n");
    printf("ID 7 power 0: Off, 1: On\n");
    printf("ID 6 data 0: No Data, 1: Data Queued\n");
    printf("ID 5 activity 0: Off, 1: On\n");
    printf("ID 4 error 0: No Error, 1: Error\n");
    printf("ID 2 performance 0: None, 1: Low, 2: Optimal, 3: High\n");
    printf("ID 0 resource 0: None, 1: Low, 2: Sufficient, 3: High\n");
    printf("<--------------------------------------------------------->\n");

    return ERR_SUCCESS;
}