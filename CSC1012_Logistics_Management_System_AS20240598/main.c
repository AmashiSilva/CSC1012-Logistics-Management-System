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

int main()
{
    initialize_system();
    int choice;
    do {
        display_main_menu();
        choice = get_valid_int_input("Enter your choice: ", 0, 5);

        switch(choice) {
            case 1:
                //To be implemented
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

