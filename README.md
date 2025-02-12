Game Name: Rocket Realm 🚀
Rocket Realm is an interactive experience where users can add, remove, filter, and manipulate rocket data and statuses. Design and customize your unique collection of rockets, manage their statuses, and showcase your creations to friends!


# Features
    Add Rockets: Create rockets with unique names.
    Modify Data: Update rocket data values to reflect custom attributes.
    Set Status: Assign and manage statuses for each rocket.
    Filter Rockets: Use bit manipulation to efficiently filter and search rockets based on specific statuses.
    Compare Collections: Build your own collection and share it with friends for fun comparisons!

# Game Tutorial
    Launch the program to see a menu with various options.
    Typically, start by typing 1 to add a rocket with a name of your choice.
    Modify the rocket’s data by selecting option 7 or set its status using option 4.
    Use the filtering feature to create a custom collection of rockets based on their statuses.
    Compare your collection with friends and see who’s the ultimate Rocketeer!

# Compilation Instructions
    To compile the code, ensure all files are in the same folder. Open your console and type:
    gcc -o rocket_game main.c rocket.c rocket_collection.c
    
    To run the program, type:
    ./rocket_game

# Technical Highlights
    Bit Manipulation: Utilized for efficient filtering and status management, enabling compact and optimized logic.
    Dynamic Data Management: Modular design allows seamless additions, updates, and filtering of rockets.
    C Programming Expertise: Demonstrates proficiency in handling low-level operations and memory-efficient programming.

# Automated Testing
To ensure reliability and correctness, Rocket Realm includes automated unit tests using CUnit.

## Running Unit Tests
1. Compile the tests by running the following command in the terminal:
   make test
   This will generate the test executable named test_rocketsys.

2. Run the test suite by executing:
   make runtest
   This will execute all unit tests and display the results in the terminal.

3. Expected output:
   Running Rocket System Tests...
   [✔] Rocket Initialization - PASSED
   [✔] Set and Validate Status - PASSED
   [✔] Data Set & Get - PASSED
   [✔] Rocket Collection Initialization - PASSED
   [✔] Appending to Collection - PASSED
   [✔] Finding a Rocket - PASSED
   [✔] Removing a Rocket - PASSED
   [✔] Filtering Rockets - PASSED

## Understanding the Commands:
- make test compiles the unit tests into an executable.
- make runtest runs the unit tests and displays results.
- make clean removes compiled files and resets the environment.

## Automated Testing Includes:
- Unit Testing validates individual functions in CUnit.
- Test Suites group related test cases for structured validation.
- Assertions verify expected vs. actual results for correctness.
- Debugging with GDB ensures accurate error tracing and system stability.
If a test fails, check the output for errors and debug using:
   gdb ./test_rocketsys
Then use:
   run
   bt
to inspect the stack trace and locate the issue.

By following these steps, you can ensure Rocket Realm functions correctly and efficiently.

