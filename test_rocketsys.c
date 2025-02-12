#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "rocket.h"
#include <string.h>

// Global Test Variables
Rocket test_rocket;
RocketCollection test_collection;

// Setup and Teardown Functions
void setup_rocket() {
    rocketsys_init(&test_rocket, "Apollo", 0);
}

void setup_collection() {
    rocketsys_collection_init(&test_collection);
}

// Rocket Initialization
void test_rocketsys_init() {
    Rocket r;
    CU_ASSERT_EQUAL(rocketsys_init(&r, "Falcon9", 0), ERR_SUCCESS);
    CU_ASSERT_STRING_EQUAL(r.name, "Falcon9");
    CU_ASSERT_EQUAL(r.status, 0);
    CU_ASSERT_EQUAL(r.data, 0);
}

// Status Setting
void test_rocketsys_status_set() {
    setup_rocket();

    CU_ASSERT_EQUAL(rocketsys_status_set(&test_rocket, STATUS_POWER, 1), ERR_SUCCESS);
    CU_ASSERT_EQUAL(((test_rocket.status >> 7) & 1), 1);

    CU_ASSERT_EQUAL(rocketsys_status_set(&test_rocket, STATUS_POWER, 0), ERR_SUCCESS);
    CU_ASSERT_EQUAL(((test_rocket.status >> 7) & 1), 0);

    CU_ASSERT_EQUAL(rocketsys_status_set(&test_rocket, STATUS_ERROR, 2), ERR_INVALID_STATUS);
}

// Test Data Setting and Retrieval
void test_rocketsys_data_set_get() {
    setup_rocket();
    unsigned int old_data = 0;

    CU_ASSERT_EQUAL(rocketsys_data_set(&test_rocket, 0xABCD1234, &old_data), ERR_SUCCESS);
    CU_ASSERT_EQUAL(test_rocket.data, 0xABCD1234);

    unsigned int retrieved_data;
    CU_ASSERT_EQUAL(rocketsys_data_get(&test_rocket, &retrieved_data), ERR_SUCCESS);
    CU_ASSERT_EQUAL(retrieved_data, 0xABCD1234);
}

// Rocket Collection Initialization
void test_rocketsys_collection_init() {
    RocketCollection collection;
    CU_ASSERT_EQUAL(rocketsys_collection_init(&collection), ERR_SUCCESS);
    CU_ASSERT_EQUAL(collection.size, 0);
}

// Appending to Rocket Collection
void test_rocketsys_append() {
    setup_collection();
    Rocket r;
    rocketsys_init(&r, "TestRocket", 0);

    CU_ASSERT_EQUAL(rocketsys_append(&test_collection, &r), ERR_SUCCESS);
    CU_ASSERT_EQUAL(test_collection.size, 1);
    CU_ASSERT_STRING_EQUAL(test_collection.rockets[0].name, "TestRocket");
}

// Finding a Rocket in the Collection
void test_rocketsys_find() {
    setup_collection();
    Rocket r;
    rocketsys_init(&r, "Voyager", 0);
    rocketsys_append(&test_collection, &r);

    CU_ASSERT_EQUAL(rocketsys_find(&test_collection, "Voyager"), 0);
    CU_ASSERT_EQUAL(rocketsys_find(&test_collection, "NonExistent"), ERR_SYS_NOT_FOUND);
}

// Removing a Rocket from Collection
void test_rocketsys_remove() {
    setup_collection();
    Rocket r;
    rocketsys_init(&r, "TestRocket", 0);
    rocketsys_append(&test_collection, &r);

    CU_ASSERT_EQUAL(rocketsys_remove(&test_collection, 0), ERR_SUCCESS);
    CU_ASSERT_EQUAL(test_collection.size, 0);
}

// Testing the Rocket Filtering
void test_rocketsys_filter() {
    setup_collection();
    Rocket r1, r2;
    rocketsys_init(&r1, "RocketA", 0);
    rocketsys_init(&r2, "RocketB", 0);
    rocketsys_append(&test_collection, &r1);
    rocketsys_append(&test_collection, &r2);

    RocketCollection filtered;
    rocketsys_collection_init(&filtered);

    CU_ASSERT_EQUAL(rocketsys_filter(&test_collection, &filtered, "*******1"), ERR_SUCCESS);
}

// Test Runner
int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Rocket System Tests", NULL, NULL);
    CU_add_test(suite, "Rocket Initialization", test_rocketsys_init);
    CU_add_test(suite, "Set and Validate Status", test_rocketsys_status_set);
    CU_add_test(suite, "Data Set & Get", test_rocketsys_data_set_get);
    CU_add_test(suite, "Rocket Collection Initialization", test_rocketsys_collection_init);
    CU_add_test(suite, "Appending to Collection", test_rocketsys_append);
    CU_add_test(suite, "Finding a Rocket", test_rocketsys_find);
    CU_add_test(suite, "Removing a Rocket", test_rocketsys_remove);
    CU_add_test(suite, "Filtering Rockets", test_rocketsys_filter);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
