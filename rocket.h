#include <stdio.h>
#include <string.h>

// Error Codes
#define ERR_SUCCESS 0
#define ERR_INVALID_INDEX -1
#define ERR_NO_DATA -2
#define ERR_INVALID_STATUS -3
#define ERR_MAX_CAPACITY -4
#define ERR_NULL_POINTER -5
#define ERR_SYS_NOT_FOUND -6

// Status Bits
#define STATUS_POWER 7
#define STATUS_DATA 6
#define STATUS_ACTIVITY 5
#define STATUS_ERROR 4
#define STATUS_PERFORMANCE 2
#define STATUS_RESOURCE 0

// Magic Numbers
#define MAX_STR 32
#define MAX_ARR 100

// Rocket Structure
typedef struct {
    char name[MAX_STR];
    unsigned char status;
    unsigned int data;
} Rocket;

// Rocket Collection Structure
typedef struct {
    Rocket rockets[MAX_ARR];
    unsigned int size;
} RocketCollection;

// Forward Declarations
int rocketsys_init(Rocket *rocket, const char *name, char status);
int rocketsys_collection_init(RocketCollection *rockets);
int rocketsys_append(RocketCollection *rockets, const Rocket *rocket);
int rocketsys_find(const RocketCollection *rockets, const char *name);
int rocketsys_print(Rocket *rocket);
int rocketsys_collection_print(RocketCollection *rockets);
int rocketsys_status_set(Rocket *rocket, unsigned char status, unsigned char value);
int rocketsys_status_print(const Rocket *rocket);
int rocketsys_data_set(Rocket *rocket, unsigned int new_data, unsigned int *old_data);
int rocketsys_data_get(Rocket *rocket, unsigned int *dest);
int rocketsys_remove(RocketCollection *rockets, int index);
int rocketsys_filter(const RocketCollection *src, RocketCollection *dest, const unsigned char *filter);
void rocketsys_status_conv(char *str);
