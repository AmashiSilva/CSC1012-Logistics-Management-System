#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Constants and global variables
#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define MAX_NAME_LENGTH 50

// Global arrays for system data
char cities[MAX_CITIES][MAX_NAME_LENGTH];
float distance[MAX_CITIES][MAX_CITIES];
int city_count = 0;

// Function prototypes
void initialize_system();
void display_main_menu();
int get_valid_int_input(char* prompt, int min, int max);
void clear_input_buffer();
int find_city_index(char* city_name);
void city_management();
void add_city();
void display_cities();
void rename_city();
void remove_city();

int main()
{
    initialize_system();
    int choice;
    do {
        display_main_menu();
        choice = get_valid_int_input("Enter your choice: ", 0, 5);

        switch(choice) {
            case 1:
                city_management();
                break;
            case 2:
                //To be implemented
                break;
            case 3:
                //To be implemented
                break;
            case 4:
                //To be implemented
                break;
            case 5:
                //To be implemented
                break;
            case 0:
                //To be implemented
                printf("Thank you for using Logistics Management System!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);

    return 0;
}

void initialize_system() {
    // Initialize distance matrix
    for(int i = 0; i < MAX_CITIES; i++) {
        for(int j = 0; j < MAX_CITIES; j++) {
            if(i == j)
                distance[i][j] = 0;
            else
                distance[i][j] = -1; //No connection
        }
    }

    //...
    printf("System initialized successfully!\n");
}

void display_main_menu() {
    printf("\n========================================\n");
    printf("   LOGISTICS MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. City Management\n");
    printf("2. Distance Management\n");
    printf("3. Process Delivery\n");
    printf("4. Reports\n");
    printf("5. Save Data\n");
    printf("0. Exit\n");
    printf("========================================\n");
}

// Input validation functions
int get_valid_int_input(char* prompt, int min, int max) {
    int value;
    while(1) {
        printf("%s", prompt);
        if(scanf("%d", &value) == 1) {
            if(value >= min && value <= max) {
                clear_input_buffer();
                return value;
            }
        }
        printf("Invalid input! Please enter a number between %d and %d.\n", min, max);
        clear_input_buffer();
    }
}

void clear_input_buffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int find_city_index(char* city_name) {
    for(int i = 0; i < city_count; i++) {
        if(strcmp(cities[i], city_name) == 0) {
            return i;
        }
    }
    return -1;
}

void city_management() {
    int choice;
    do {
        printf("\n--- City Management ---\n");
        printf("1. Add City\n");
        printf("2. Rename City\n");
        printf("3. Remove City\n");
        printf("4. Display Cities\n");
        printf("0. Back to Main Menu\n");

        choice = get_valid_int_input("Enter your choice: ", 0, 4);

        switch(choice) {
            case 1:
                add_city();
                break;
            case 2:
                rename_city();
                break;
            case 3:
                remove_city();
                break;
            case 4:
                display_cities();
                break;
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 0);
}

void add_city() {
    if(city_count >= MAX_CITIES) {
        printf("Maximum number of cities (%d) reached!\n", MAX_CITIES);
        return;
    }

    char city_name[MAX_NAME_LENGTH];
    printf("Enter city name: ");
    scanf("%49s", city_name);
    clear_input_buffer();

    if(find_city_index(city_name) != -1) {
        printf("City '%s' already exists!\n", city_name);
        return;
    }

    strcpy(cities[city_count], city_name);
    city_count++;
    printf("City '%s' added successfully!\n", city_name);
}

void display_cities() {
    printf("\n--- Available Cities ---\n");
    if(city_count == 0) {
        printf("No cities available.\n");
        return;
    }

    for(int i = 0; i < city_count; i++) {
        printf("%d. %s\n", i + 1, cities[i]);
    }
}

void rename_city() {
    if(city_count == 0) {
        printf("No cities available!\n");
        return;
    }

    display_cities();
    int index = get_valid_int_input("Enter city number to rename: ", 1, city_count) - 1;

    char new_name[MAX_NAME_LENGTH];
    printf("Enter new name for %s: ", cities[index]);
    scanf("%49s", new_name);
    clear_input_buffer();

    if(find_city_index(new_name) != -1) {
        printf("City '%s' already exists!\n", new_name);
        return;
    }

    printf("City '%s' renamed to '%s'\n", cities[index], new_name);
    strcpy(cities[index], new_name);
}

void remove_city() {
    if(city_count == 0) {
        printf("No cities available!\n");
        return;
    }

    display_cities();
    int index = get_valid_int_input("Enter city number to remove: ", 1, city_count) - 1;

    printf("Are you sure you want to remove '%s'? (1=Yes, 0=No): ", cities[index]);
    int confirm = get_valid_int_input("", 0, 1);

    if(confirm) {
        // Shift array to remove city
        char removed_city[MAX_NAME_LENGTH];
        strcpy(removed_city, cities[index]);

        for(int i = index; i < city_count - 1; i++) {
            strcpy(cities[i], cities[i + 1]);
        }
        city_count--;

        printf("City '%s' removed successfully!\n", removed_city);
    }
}
